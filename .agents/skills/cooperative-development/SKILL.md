---
name: cooperative-development
description: Orchestrate multiple specialized agents to work together on Blueprint features with defined roles and quality gates.
---

# Cooperative Development

**Context reuse:** This skill coordinates the work of specialized sub-agents, each with limited context and specific responsibilities.

## Overview

The cooperative development skill orchestrates a team of AI agents to implement Blueprint features through a simplified MVP workflow:

- **Coordinator** - Main orchestrator that manages the process and delegates work
- **Architect** - Analyzes requirements and creates specifications
- **Critic** - Reviews architectural decisions and specifications  
- **Developer** - Implements code step-by-step according to specifications
- **Reviewer** - Performs technical review of each implementation step

## Workflow

1. **Task Reception** - Coordinator receives task from user
2. **Architectural Specification** - Architect creates specifications, Critic reviews
3. **User Approval** - Specifications reviewed by user
4. **Iterative Implementation** - Developer implements step-by-step with Reviewer feedback for each step
5. **Final Verification** - Coordinator runs final Blueprint checks
6. **User Acceptance** - Final user review and approval

## Coordinator Responsibilities

The coordinator agent (running this skill) must:

1. Create and maintain task context in `blueprint/context/cooperative/`
2. Delegate work to appropriate sub-agents via `new_task`
3. Validate outputs from each agent
4. Manage iteration loops (revisions, fixes)
5. Handle user gates and approvals
6. Ensure final quality through Blueprint checks

## Detailed Workflow Implementation

### Phase 1: Architectural Specification

#### Step 1.1: Task Initialization
1. Create `blueprint/context/cooperative/current-task-context.md`
2. Populate with task information from build plan or user request
3. Set initial status to "Architectural Phase"

#### Step 1.2: Architect Assignment
1. Read `architect-role.md` to understand architect responsibilities
2. Prepare architect context including:
   - Task description and requirements
   - Project architecture constraints
   - Expected outputs specification
3. Launch architect via `new_task`:
```yaml
mode: architect (or appropriate mode)
message: |
  You are an architect in the cooperative development framework. Your task: [task description]
  
  Task context: [project context]
  Input data: [what is provided]
  Expected results: [what should be created]
```

#### Step 1.3: Architect Output Processing
1. Wait for architect completion
2. Validate architect output:
   - Check that `blueprint/context/current-feature.md` is created
   - Verify specification completeness
   - Confirm architectural decisions documented
3. Create `architect-output.md` with summary of architect work
4. Update `current-task-context.md` status

#### Step 1.4: Feature Branch Creation
1. **Check Current Branch:** Verify we're not already on a feature branch
2. **Create Feature Branch:**
   - Use branch name from specification or generate from task title
   - Follow naming convention: `feature/kebab-case-title`
   - Branch prefix from `blueprint/config.json`: `feature/`
3. **Update Specification:** Ensure `current-feature.md` contains correct branch name
4. **Switch to Feature Branch:** Use `git checkout -b <branch-name>`
5. **Update Context:** Record branch creation in task context

#### Step 1.5: Critic Assignment
1. Read `critic-role.md` to understand critic responsibilities
2. Prepare critic context including:
   - Architect's specification (`current-feature.md`)
   - Architect's output summary (`architect-output.md`)
   - Project standards and requirements
   - Expected review criteria
3. Launch critic via `new_task`:
```yaml
mode: architect (or appropriate mode for review)
message: |
  You are a critic in the cooperative development framework. Your task: review architectural decisions and specifications created by the architect.
  
  Task context: [task description]
  Input data from architect: [links to specification and report]
  Project requirements: [architectural standards]
  Your task as critic: [what to check]
  Expected results: [report format]
```

#### Step 1.5: Critic Output Processing
1. Wait for critic completion
2. Validate critic output:
   - Check creation of `critic-feedback.md`
   - Verify structured feedback with priority levels
   - Confirm clear approval status
3. Update `current-task-context.md` with critic status
4. Analyze critic feedback to determine next steps:
   - If **Approved**: Proceed to user approval
   - If **Needs Revision**: Return to architect with specific issues
   - If **Rejected**: Reevaluate task approach

#### Step 1.6: Iteration Management (Revision Cycles)

**When critic returns "Needs Revision" status:**

1. **Create Revision Request:**
   - Create `revision-request-XXX.md` file using standardized template:
```markdown
# Revision Request #[number]

**Task:** [Task name]  
**Request Date:** [Date]  
**From:** Coordinator (based on critic feedback)  
**To:** [Role - Architect/Developer/etc.]  
**Priority:** [High/Medium/Low]  
**Revision Cycle:** [number] of [maximum] maximum

## Summary

[Brief summary of why revision is needed]

## Critical Issues (Must Address)

### P1: [Critical Issue Title]
**Problem:** [Detailed problem description]
**Critic Recommendation:** [Specific recommendation from critic]
**Required Changes:**
1. [Change 1]
2. [Change 2]
3. [Change 3]

### P2: [Major Issue Title]  
**Problem:** [Detailed problem description]
**Critic Recommendation:** [Specific recommendation from critic]
**Required Changes:**
1. [Change 1]
2. [Change 2]

## Specific Revision Tasks

### Task 1: [Task description]
- [ ] Subtask 1.1
- [ ] Subtask 1.2

### Task 2: [Task description]  
- [ ] Subtask 2.1
- [ ] Subtask 2.2

## Expected Deliverables

1. [Deliverable 1 - e.g., Updated specification]
2. [Deliverable 2 - e.g., Documentation of decisions]
3. [Deliverable 3 - e.g., Ready for re-review]

## Quality Criteria for Revision

The revised work should:
- [ ] Resolve all P1 critical issues
- [ ] Address P2 major concerns with clear solutions
- [ ] Maintain architectural compliance with project standards
- [ ] Preserve all original functional requirements
- [ ] Remain implementable within reasonable complexity

## Timeline

**Requested Completion:** [Timeline]  
**Re-review:** Immediate after revision completion  
**Maximum Cycles:** [number] (this is cycle [current])

---

**Coordinator Note:** [Additional context or instructions]
```
   - Number revisions sequentially (001, 002, etc.)
   - Include specific, actionable tasks
   - Set clear quality criteria
   - Define maximum iteration limits (recommended: 3 cycles)

2. **Return to Architect:**
```yaml
mode: architect
message: |
  You are an architect. The specification requires revision based on critic feedback.
  
  Revision context:
  - Specification: `blueprint/context/current-feature.md`
  - Critic feedback: `blueprint/context/cooperative/critic-feedback.md`
  - Revision request: `blueprint/context/cooperative/revision-request-XXX.md`
  
  Critical issues:
  [List P1 issues from critic feedback]
  
  Required changes:
  [Specific tasks from revision request]
  
  Expected results:
  1. Updated specification `current-feature.md`
  2. Documentation of decisions made
  3. Readiness for re-review
  
  This is revision [number] of [maximum] allowed cycles.
```

3. **Track Revision Progress:**
   - Update `current-task-context.md` with revision status
   - Add to decision log with revision details
   - Monitor maximum iteration limits (recommended: 3 cycles)

4. **Process Revised Specification:**
   - Verify architect completed revision tasks
   - Check that critical issues are addressed
   - Prepare for critic re-review

5. **Return to Critic for Re-review:**
```yaml
mode: architect
message: |
  You are a critic. The architect has completed specification revision.
  
  Revision context:
  - Original specification: [link to original]
  - Critic feedback: `critic-feedback.md`
  - Revision request: `revision-request-XXX.md`
  - Updated specification: `current-feature.md`
  
  Your task:
  1. Verify that critical issues (P1) are resolved
  2. Assess quality of fixes
  3. Determine if any unresolved issues remain
  4. Update status: Approved/Needs Revision/Rejected
  
  Expected result:
  Updated `critic-feedback.md` with revision assessment.
```

6. **Iteration Completion:**
   - Continue until "Approved" status
   - Escalate after maximum iterations
   - Document final iteration outcomes

#### Step 1.7: User Approval Gate

**When critic returns "Approved" status:**

1. **Prepare User Approval Package:**
   - Complete specification: `current-feature.md`
   - Architect output: `architect-output.md`
   - Critic feedback: `critic-feedback.md` (final approved version)
   - Revision history: All `revision-request-XXX.md` files
   - Task context: `current-task-context.md`

2. **Present to User:**
```
## User Approval Required

**Task:** [Task name and description]
**Status:** Specification approved by critic, ready for user approval

**Specification Summary:**
- [Brief summary of what will be implemented]
- [Key architectural decisions made]
- [Scope and limitations]

**Review Materials:**
1. Full specification: `blueprint/context/current-feature.md`
2. Architect analysis: `blueprint/context/cooperative/architect-output.md`
3. Critic review: `blueprint/context/cooperative/critic-feedback.md`
4. Revision history: [List of revision files]

**Approval Request:**
Please review the specification and provide:
- [ ] Approval to proceed with implementation
- [ ] Request for specific changes (return to architect)
- [ ] Rejection with rationale (task reevaluation)

**Next steps after approval:**
- QA engineer creates acceptance tests (parallel)
- Developer begins implementation
- Reviewer assigned for step-by-step review
```

3. **Process User Response:**
   - **If approved:** Update context, proceed to Phase 2
   - **If changes requested:** Create user-change-request.md, return to architect
   - **If rejected:** Document rationale, reevaluate task approach

4. **Update Task Context:**
   - Mark user approval status
   - Document approval decision
   - Prepare for next development phase

#### Step 1.8: Next Phase Transition
1. After user approval: Proceed to Phase 2 (Iterative Implementation)
2. If changes requested: Return to architect with user feedback
3. If rejected: Document and reevaluate task approach

### Phase 2: Iterative Implementation (Developer + Reviewer)

#### Step 2.1: Developer Assignment for Current Step
1. Identify current step from `current-feature.md` specification
2. Prepare developer context with specific step requirements
3. Include: TDD requirements, quality gate compliance, verification commands
4. Launch developer subagent with step-specific instructions

#### Step 2.2: Developer Implementation & Commit
1. Developer implements step using TDD approach
2. Creates/modifies implementation files and tests
3. Runs verification commands to confirm red phase (if applicable)
4. Creates implementation report documenting work
5. Commits changes to feature branch with descriptive message

#### Step 2.3: Create Review Request
1. Create review request using template: `reference/review-request-template.md`
2. Save as `blueprint/context/cooperative/review-request-###.md` (### = sequential number)
3. Include in review request:
   - Specification requirements for the step
   - Files to review (analysis, implementation, tests)
   - Verification commands for reviewer
   - Success criteria and quality gate compliance checks
4. Update `current-task-context.md` with review request creation

#### Step 2.4: Launch Reviewer Subagent
1. Prepare reviewer context referencing the review request file
2. Launch reviewer subagent with instructions to:
   - Read `review-request-###.md` for full context
   - Perform comprehensive code review
   - Use template: `reference/reviewer-report-template.md`
   - Save report as `reviewer-report-###-actual.md`
   - Return approval status (Approved/Needs Revision/Rejected)
3. Set review deadline (typically 24 hours)

#### Step 2.5: Process Review Results
1. Reviewer creates structured report using standardized template
2. Report includes: overall assessment, issue classification (P1/P2/P3), risk assessment, verification performed
3. Coordinator reads report and determines next steps:
   - **If Approved:** Mark step complete, update task context, proceed to next step
   - **If Needs Revision:** Create revision request for developer, return to Step 2.2
   - **If Rejected:** Assess reasons, may require architectural re-evaluation

#### Step 2.6: Update Task Context
1. Update `current-task-context.md` using template: `reference/task-context-template.md`
2. Record step completion status and reviewer assessment
3. Add decision log entry for the step cycle
4. Update agent assignments status

#### Step 2.7: Repeat for Remaining Steps
1. Continue Steps 2.1-2.6 for each step in specification
2. Maintain sequential step progression
3. Track overall progress in task context
4. Handle any iteration cycles for revisions

#### Step 2.8: Final Step Completion
1. After last step implementation and review:
   - Run final verification commands from specification
   - Ensure all quality gates satisfied
   - Verify no regression in existing functionality
   - Prepare for Phase 3: Final Verification

## Key Improvements from Practical Testing:

### Template Standardization
- **Review Requests:** Use `reference/review-request-template.md` for consistent structure
- **Reviewer Reports:** Use `reference/reviewer-report-template.md` with `-actual` suffix
- **Task Context:** Use `reference/task-context-template.md` for status tracking

### Context Management
- **Self-contained Context:** Each review request contains all information reviewer needs
- **File References:** Include exact paths, commit hashes, specification sections
- **Verification Evidence:** Document actual test outputs and build results

### Process Efficiency
- **Parallel Ready:** Review requests enable parallel subagent execution
- **Clear Handoffs:** Structured templates ensure clean transitions between roles
- **Audit Trail:** All decisions and assessments documented in context files

## Sub-Agent Roles

Each role has a dedicated role description file in this directory:
- `architect-role.md` - Architecture and specification creation
- `critic-role.md` - Architectural and specification review
- `developer-role.md` - Code implementation
- `reviewer-role.md` - Technical code review

## Context Management

All context files are stored in `blueprint/context/cooperative/` using standardized templates from `reference/` directory:

### Core Context Files:
- `current-task-context.md` - Current task description and overall status (use `reference/task-context-template.md`)
- `architect-output.md` - Specifications from architect
- `critic-feedback.md` - Feedback from critic
- `revision-request-###.md` - Revision requirements for iterations
- `architect-decisions-###.md` - Architectural decision documentation

### Review Cycle Files:
- `review-request-###.md` - Review requests for implementation steps (use `reference/review-request-template.md`)
- `reviewer-report-###-actual.md` - Actual reviewer output (use `reference/reviewer-report-template.md`)
- `reviewer-report-###.md` - Template/example reviewer reports

### Template-Based Management:
1. **Consistency:** All files follow standardized templates for predictable structure
2. **Project-Agnostic:** Templates use `[bracketed]` placeholders for project-specific details
3. **Reference Directory:** Contains all templates: `reference/review-request-template.md`, `reference/reviewer-report-template.md`, `reference/task-context-template.md`
4. **Naming Convention:** Sequential numbering (###) for related files

### Best Practices from Testing:
- **Self-contained Context:** Each review request contains all information reviewer needs
- **Evidence Inclusion:** Include actual test outputs, commit hashes, verification results
- **Structured Reporting:** Use P1/P2/P3 issue classification with specific locations
- **Quality Gate Integration:** Explicit compliance checks with project quality gates

**Project Quality Standards:**
The coordinator automatically includes `blueprint/context/quality-gates.md` in the context for all agents when it exists. This file contains project-specific quality standards that must be followed by:
- **Architect** - Must ensure specifications comply with quality gates
- **Critic** - Must verify quality gate compliance in reviews
- **Developer** - Must follow quality gates during implementation
- **QA Engineer** - Must create tests meeting quality standards

## Integration with Blueprint

This skill builds upon existing Blueprint skills with enhanced coordination:

### Skill Integration:
- **Architect Role:** Uses `/feature` process for specification creation
- **Developer Role:** Uses `/implement` approach for step-by-step implementation  
- **Reviewer Role:** Uses `/audit` methodology for code review with structured reporting
- **Quality Gates:** Integrates `quality-gates.md` requirements throughout workflow
- **Verification:** Uses `/check` for final verification cycles

### Template-Based Workflow:
1. **Standardized Templates:** All coordination uses templates from `reference/` directory
2. **Context Files:** Follow Blueprint context directory structure in `blueprint/context/cooperative/`
3. **Quality Compliance:** Explicit quality gate checks integrated into all review processes
4. **Audit Trail:** All decisions documented in context files for traceability

### Key Enhancements from Practical Testing:
- **Self-contained Context:** Review requests contain complete information for subagent execution
- **Structured Reporting:** Standardized templates ensure consistent output quality
- **Evidence-Based:** Includes actual verification results, test outputs, commit references
- **Iteration Management:** Clear revision cycles with issue prioritization (P1/P2/P3)

### Compatibility:
- Maintains full compatibility with existing Blueprint workflow
- Can run alongside standard `/feature` → `/implement` → `/check` cycles
- Preserves all Blueprint quality gates and verification steps
- Uses same context directory structure for easy integration

## Starting a Task

To start cooperative development on a task:

1. **Prepare Environment:**
   - Ensure `blueprint/context/current-feature.md` is empty
   - Verify `blueprint/context/quality-gates.md` exists (create if needed for project standards)
   - Check that `blueprint/context/cooperative/` directory exists or will be created

2. **Initialize Task:**
   - Run this skill with the task description or build-plan item number
   - Coordinator creates `current-task-context.md` using `reference/task-context-template.md`
   - Quality gates automatically integrated into all review processes

3. **Workflow Execution:**
   - Work proceeds through Phase 1 (Architectural Specification) with critic review
   - After user approval, enters Phase 2 (Iterative Implementation)
   - Each implementation step follows: Developer → Review Request → Reviewer cycle
   - All coordination uses standardized templates from `reference/` directory

4. **Template Usage:**
   - **Review Requests:** `reference/review-request-template.md` → `review-request-###.md`
   - **Reviewer Reports:** `reference/reviewer-report-template.md` → `reviewer-report-###-actual.md`
   - **Task Context:** `reference/task-context-template.md` → `current-task-context.md`
   - Sequential numbering (###) maintains file relationships

5. **Quality Assurance:**
   - All work includes quality gate compliance verification
   - Structured reporting with issue prioritization (P1/P2/P3)
   - Evidence-based verification with actual test outputs
   - Audit trail in context files for complete traceability

## Practical Example: Architect Phase

### Example Task: Build Plan Item #2 "Unify menu organization principles"

#### Coordinator Actions Performed:
1. **Created context directory and files:**
   - `blueprint/context/cooperative/README.md`
   - `blueprint/context/cooperative/current-task-context.md`

2. **Assigned architect with this context:**
```yaml
mode: architect
message: |
  You are an architect in the cooperative development framework. Your task: create specification for Build Plan Item #2 "Unify menu organization principles".
  
  Task context:
  - Project: MIDI Patch Box (embedded C++ system with PlatformIO)
  - Current state: Project uses two different menu approaches that need unification
  - Architecture: State pattern with DI container
  - Quality gates: See `blueprint/context/quality-gates.md` for project standards
  - Requirement: Standardize menu architecture to use consistent patterns
  
  Input data:
  1. Build Plan Item #2: "Unify menu organization principles..."
  2. Project files available in workspace
  3. Quality gates file: `blueprint/context/quality-gates.md` (includes TDD requirements)
  4. Architectural requirements: preserve State pattern, DI container, ensure testability
  
  Expected results:
  1. Complete `blueprint/context/current-feature.md` specification file
  2. Ensure specification complies with quality gates (TDD, testing, build verification)
  3. Architectural decisions and rationale
  4. Identified dependencies
  5. Open questions (if any)
```

3. **Processed architect output:**
   - Verified `current-feature.md` creation
   - Created `architect-output.md` with architect findings
   - Updated task context status

4. **Feature branch created:**
   - Branch name: `feature/unify-menu-organization-principles`
   - Based on specification in `current-feature.md`
   - Branch switched successfully
   - Context updated with branch information

5. **Critic review performed:**
```yaml
mode: architect
message: |
  You are a critic in the cooperative development framework. Your task: review architectural decisions and specifications created by the architect for task "Unify menu organization principles".
  
  Task context:
  - Project: MIDI Patch Box (embedded C++ system with PlatformIO)
  - Project architecture: State pattern with DI container
  - Quality gates: See `blueprint/context/quality-gates.md` for project standards
  - Requirement: Unify two different menu approaches
  
  Input data from architect:
  1. Specification: `blueprint/context/current-feature.md`
  2. Architect report: `blueprint/context/cooperative/architect-output.md`
  3. Key architect decisions: unification under MenuController, interface inheritance
  
  Project requirements:
  - Preserve State pattern architecture
  - Maintain DI container and interface design
  - Ensure testability through native target
  - Comply with quality gates in `quality-gates.md`
  
  Your task as critic:
  1. **Quality Gate Verification**: Check specification compliance with `quality-gates.md`
  2. Verify compliance of proposed architecture with project standards
  3. Assess specification completeness including TDD steps
  4. Evaluate technical feasibility
  5. Identify potential risks
  6. Suggest improvements or alternatives
  
  Expected results:
  1. Structured report with findings including quality gate compliance
  2. Approval status: Approved/Needs Revision/Rejected
  3. Specific issues with fix recommendations
  4. Quality gate compliance assessment
  5. Risk assessment
```

5. **Processed critic output:**
   - Received `critic-feedback.md` with detailed review
   - Status: "Specification Needs Revision"
   - Critical issues identified: interface semantics mismatch, DI container strategy
   - Updated task context with critic status

6. **Critic iteration cycle started:**
```yaml
# Revision request created: revision-request-001.md
# Key issues addressed:
# 1. P1: Interface semantics mismatch → Adapter pattern instead of inheritance
# 2. P2: DI Container strategy undefined → Explicit DI changes required
# 3. P3: EditSetlistState ambiguity → Clear decision needed

# Next steps prepared:
# - Return to architect with revision request
# - Architect revises specification
# - Critic re-reviews revised specification
# - Continue until "Approved" status
```

7. **Iteration cycle completed:**
   - Specification v1.0 → v2.0 after revision
   - All critical issues resolved: P1 (Adapter pattern), P2 (DI container), P3 (EditSetlistState)
   - Critic re-review: APPROVED
   - Cycle efficiency: Single iteration sufficient
   - Artifacts: revision-request-001.md, architect-decisions-001.md

8. **Current status:**
   - Architectural specification phase COMPLETE
   - Specification v2.0 approved by critic
   - Ready for user approval gate
   - Next: Iterative Implementation with Developer and Reviewer

## Quality Gates

The coordinator enforces quality gates:
- Architectural review by critic before implementation
- User approval of specifications
- Step-by-step review during implementation by Reviewer
- Final Blueprint verification
- User final approval

## Best Practices from Practical Testing

### Iteration Cycle Optimization

**Effective patterns identified:**
1. **Issue prioritization:** Use P1/P2/P3 classification for clear focus
2. **Specific requirements:** Provide concrete tasks in revision requests
3. **Documentation tracking:** Maintain `architect-decisions-XXX.md` for transparency
4. **Cycle limits:** Maximum 3 iterations prevents endless revisions

**Template standardization:**
- Revision requests follow consistent format
- Critic feedback uses structured P1/P2/P3 classification
- Architectural decisions documented separately
- Task context updated after each phase

### Communication Guidelines

**For architect assignments:**
- Include specific quality criteria
- Reference existing artifacts (specifications, feedback)
- Set clear expectations for deliverables
- Define success criteria upfront

**For critic reviews:**
- Structure feedback with priority levels
- Provide concrete recommendations
- Assess architectural compliance
- Give clear approval status

### Context Management

**File organization:**
- `current-task-context.md` - Overall status and decisions (use `reference/task-context-template.md`)
- `architect-output.md` - Architect work products
- `critic-feedback.md` - Feedback from critic
- `revision-request-###.md` - Revision requirements for iterations
- `architect-decisions-###.md` - Architectural decision documentation
- `review-request-###.md` - Review requests for implementation steps (use `reference/review-request-template.md`)
- `reviewer-report-###-actual.md` - Actual reviewer output (use `reference/reviewer-report-template.md`)

**Template-based workflow:**
1. **Standardized Structure:** All coordination files follow templates in `reference/` directory
2. **Self-contained Context:** Each review request contains complete information for subagent execution
3. **Evidence Inclusion:** Actual test outputs, commit hashes, verification results
4. **Structured Reporting:** P1/P2/P3 issue classification with specific file:line references
5. **Quality Gate Integration:** Explicit compliance checks with project quality gates

**Status tracking:**
- Update context after each agent completes work
- Maintain iteration count and cycle limits
- Document key decisions in decision log
- Track progress through workflow phases

### Subagent Execution Patterns

**Effective subagent coordination:**
1. **Complete Context:** Provide all needed information in review request files
2. **Standardized Templates:** Use templates for predictable input/output structure
3. **Clear Instructions:** Include exact commands for verification and reporting
4. **Evidence Requirements:** Specify what evidence should be included in reports
5. **Structured Output:** Require standardized report format for easy processing

**Reviewer subagent success factors:**
- **Comprehensive Context:** Review request includes specification, files, verification commands
- **Template Usage:** Reviewer uses standardized report template with `-actual` suffix
- **Evidence-Based:** Includes actual test outputs, build results, code references
- **Structured Assessment:** Clear approval status with P1/P2/P3 issue classification
- **Actionable Recommendations:** Specific fixes with file:line locations

**Coordinator efficiency patterns:**
- **Template-Driven:** Create all coordination files from standardized templates
- **Sequential Numbering:** Maintain `###` sequence for related files
- **Automated Handoffs:** Structured context enables clean subagent launches
- **Progress Tracking:** Update task context after each workflow event
- **Quality Assurance:** Verify all outputs against quality gate requirements

## Practical Example: Completed Iteration Cycle

### Task: Build Plan Item #2 "Unify menu organization principles"

**Cycle 1 Results:**
- ✅ **Issues identified:** 3 critical (P1, P2, P3)
- ✅ **Revision requested:** Clear requirements in `revision-request-001.md`
- ✅ **Specification revised:** v1.0 → v2.0 with Adapter pattern
- ✅ **Critic re-review:** Approved all fixes
- ✅ **Cycle efficiency:** All issues resolved in single iteration

**Key artifacts produced:**
1. `current-feature.md` v2.0 - Approved specification
2. `critic-feedback.md` - Initial and final review
3. `revision-request-001.md` - Structured revision requirements
4. `architect-decisions-001.md` - Decision rationale documentation
5. Updated `current-task-context.md` - Complete status tracking

**Lessons applied to skill:**
- Standardized revision request template
- Clear iteration management process
- Effective agent communication patterns
- Comprehensive context documentation

---

*This skill is under active development as part of the cooperative development framework.*
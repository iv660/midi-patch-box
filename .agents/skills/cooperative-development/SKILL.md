---
name: cooperative-development
description: Orchestrate multiple specialized agents to work together on Blueprint features with defined roles and quality gates.
---

# Cooperative Development

**Context reuse:** This skill coordinates the work of specialized sub-agents, each with limited context and specific responsibilities.

## Overview

The cooperative development skill orchestrates a team of AI agents to implement Blueprint features through a coordinated workflow:

- **Coordinator** - Main orchestrator that manages the process and delegates work
- **Architect** - Analyzes requirements and creates specifications
- **Critic** - Reviews architectural decisions and specifications
- **QA Engineer** - Creates acceptance tests based on specifications
- **Developer** - Implements code according to specifications
- **Reviewer** - Performs technical review of implementation steps

## Workflow

1. **Task Reception** - Coordinator receives task from user
2. **Architectural Phase** - Architect creates specifications, Critic reviews
3. **User Approval** - Specifications reviewed by user
4. **Parallel Preparation** - QA Engineer creates tests while Developer implements
5. **Implementation Loop** - Developer works step-by-step with Reviewer feedback
6. **Final Verification** - QA Engineer runs acceptance tests, Coordinator runs final checks
7. **User Acceptance** - Final user review and approval

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
   - Create `revision-request-XXX.md` file with:
     - Summary of critical issues
     - Specific revision tasks
     - Expected deliverables
     - Timeline and quality criteria
   - Number revisions sequentially (001, 002, etc.)

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
1. After user approval: Proceed to Phase 2 (Parallel Preparation)
2. If changes requested: Return to architect with user feedback
3. If rejected: Document and reevaluate task approach

## Sub-Agent Roles

Each role has a dedicated role description file in this directory:
- `architect-role.md` - Architecture and specification creation
- `critic-role.md` - Architectural and specification review
- `qa-engineer-role.md` - Acceptance test creation
- `developer-role.md` - Code implementation
- `reviewer-role.md` - Technical code review

## Context Management

All temporary context files are stored in `blueprint/context/cooperative/`:

- `current-task-context.md` - Current task description and overall status
- `architect-output.md` - Specifications from architect
- `critic-feedback.md` - Feedback from critic
- `qa-tests.md` - Acceptance tests from QA engineer
- `implementation-status.md` - Step-by-step implementation status
- `review-feedback.md` - Review feedback from reviewer

## Integration with Blueprint

This skill builds upon existing Blueprint skills:
- Uses `/feature` through architect role
- Uses `/implement` through developer role  
- Uses `/check` for final verification
- Uses `/audit` through reviewer role
- Maintains compatibility with existing workflow

## Starting a Task

To start cooperative development on a task:

1. Ensure `blueprint/context/current-feature.md` is empty
2. Run this skill with the task description or build-plan item number
3. The coordinator will create necessary context files
4. Work will proceed through the defined workflow

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
  - Requirement: Standardize menu architecture to use consistent patterns
  
  Input data:
  1. Build Plan Item #2: "Unify menu organization principles..."
  2. Project files available in workspace
  3. Architectural requirements: preserve State pattern, DI container, ensure testability
  
  Expected results:
  1. Complete `blueprint/context/current-feature.md` specification file
  2. Architectural decisions and rationale
  3. Identified dependencies
  4. Open questions (if any)
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
  - Project architecture: State pattern with DI container, TDD approach
  - Requirement: Unify two different menu approaches
  
  Input data from architect:
  1. Specification: `blueprint/context/current-feature.md`
  2. Architect report: `blueprint/context/cooperative/architect-output.md`
  3. Key architect decisions: unification under MenuController, interface inheritance
  
  Project requirements:
  - Preserve State pattern architecture
  - Maintain DI container and interface design
  - Ensure testability through native target
  - Follow TDD development approach
  
  Your task as critic:
  1. Verify compliance of proposed architecture with project standards
  2. Assess specification completeness
  3. Evaluate technical feasibility
  4. Identify potential risks
  5. Suggest improvements or alternatives
  
  Expected results:
  1. Structured report with findings
  2. Approval status: Approved/Needs Revision/Rejected
  3. Specific issues with fix recommendations
  4. Risk assessment
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

7. **Current status:**
   - Specification v1.0 created by architect
   - Critic review completed with "Needs Revision" status
   - Revision request #001 created with specific tasks
   - Iteration cycle 1 in progress
   - Maximum iterations: 3 cycles configured

## Quality Gates

The coordinator enforces quality gates:
- Architectural review by critic before implementation
- User approval of specifications
- Step-by-step review during implementation
- Final acceptance test verification
- User final approval

---

*This skill is under active development as part of the cooperative development framework.*
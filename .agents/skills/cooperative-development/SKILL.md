---
name: cooperative-development
description: Linear automated development workflow with two human gates for specification approval and final acceptance.
---

# Cooperative Development (Linear Conveyor)

**Purpose:** Linear sequence of validated steps with two human gates: specification approval and final acceptance.

**Process:** Specification → Critic Review → Human Gate 1 → Implementation → Quality Gates → Documentation Update → Completion

**Human Gates:** (1) Specification approval, (2) Final acceptance

## Overview

**Cooperative Development** is a workflow wrapper around **Blueprint skills** that adds explicit human approval gates and custom review roles to the standard Blueprint feature development process. It orchestrates and enhances Blueprint's `/feature`, `/fix`, `/implement`, `/check`, and `/complete` skills with:

- **Two mandatory human gates** for specification approval and final acceptance
- **Isolated Critic role** for independent specification review
- **Custom reviewer roles** for TDD red-phase and code review validation
- **Artifact preservation** for full audit trail of development decisions
- **Linear execution** through isolated subagents to minimize token usage

This skill does not replace Blueprint; it coordinates Blueprint skills and supplements them with additional review and approval checkpoints.

## Architecture

This skill acts as a **lightweight coordinator** that delegates work to Blueprint skills and custom roles via subagents. Each phase uses isolated context to minimize token usage while maintaining quality through specialized execution.

**Delegation Strategy:**
- Blueprint skills are invoked through subagents in appropriate modes
- Custom roles (Critic, Reviewer) execute in specialized modes
- Each subagent receives minimal, focused context
- Results are preserved in artifact files for subsequent steps
- Coordinator maintains only process metadata and decision history

## Workflow Overview

### 1. Specification Preparation
- `/feature` or `/fix` creates `current-feature.md` with acceptance checklist
- Ensure quality gates integrated into specification

### 2. Specification Review & Human Gate 1
- Critic (separate subagent) reviews via `critic-role.md`
- **HUMAN GATE:** User approves specification after all P1 issues resolved

### 3. Linear Implementation
- Steps from `current-feature.md` executed sequentially
- TDD: red phase continues without stopping
- Step review based on project configuration

### 4. Quality Gates
- `/check` for behavioral verification
- Full test suite execution before final acceptance
- **HUMAN GATE:** User completes final acceptance checklist

### 5. Documentation Update
- Review and update project documentation per `updatable-docs.md`
- Ensure all documentation reflects implementation changes

### 6. Completion
- `/complete` after acceptance
- Archive context and artifacts

## Phase 1: Specification Preparation

### Delegation
**Blueprint Skill:** `/feature` or `/fix`  
**Execution:** Subagent in **architect** mode  
**Input Contract:** `reference/feature-request-template.md`  
**Output Contract:** `reference/feature-response-template.md`  
**Deliverable:** `blueprint/context/current-feature.md`

### Steps
1. **Context:** Coordinator creates `blueprint/context/cooperative/current-task-context.md`
2. **Branch Creation:** Ensure feature/fix branch is created with correct Blueprint prefix and format:
   - Feature: `feature/<lowercase-kebab-case-title>`
   - Fix: `fix/<lowercase-kebab-case-title>`
   - Rollback: `rollback/<lowercase-kebab-case-title>`
   - Prefix from `blueprint/config.json` `git.branchPrefix` (default: feature/, fix/, rollback/)
3. **Specification:** Launch `/feature` or `/fix` subagent in **architect** mode to create `current-feature.md` with acceptance checklist
4. **Validation:** Coordinator verifies quality gates are integrated, no blocking ambiguities

### Requirements
- Feature/fix branch created with correct prefix and kebab-case format per Blueprint conventions
- Complete, actionable specification
- Acceptance checklist for human gates
- Quality gates integrated into specification
- No architectural blockers

## Phase 2: Specification Review & Approval

### Delegation
**Custom Role:** Critic (no Blueprint skill)  
**Execution:** Subagent in **architect** mode (read + markdown only)  
**Input Contract:** `reference/critic-request-template.md`  
**Output Contract:** `reference/critic-feedback-template.md`  
**Deliverable:** `blueprint/context/cooperative/critic-feedback.md` with P1/P2/P3 findings

**If P1 Issues Present:**  
**Execution:** Subagent in **architect** mode  
**Input Contract:** `reference/p1-fix-request-template.md`  
**Output Contract:** `reference/p1-fix-response-template.md`  
**Deliverable:** Revised `current-feature.md`

### Steps
1. **Branch Verification:** Verify feature/fix branch exists with correct Blueprint prefix and format
   - Expected branch names match specification title in kebab-case
   - Prefix matches `blueprint/config.json` settings
   - Report branch status in coordinator context
2. **Critic Review:** Launch Critic subagent in **architect** mode to review specification via `critic-role.md`
3. **Feedback:** Critic creates `critic-feedback.md` with P1/P2/P3 findings
4. **Blockers:** If P1 issues exist, launch architect subagent in **architect** mode to resolve them
5. **Human Gate 1:** Present specification to user, request approval after all P1 issues resolved

### Requirements
- Feature/fix branch created with correct prefix and kebab-case format per Blueprint conventions
- Critic separate from specification author (isolated subagent)
- All P1 issues resolved before approval
- Explicit user approval recorded in task context

## Phase 3: Linear Implementation

### Delegation
**Red Phase - Write Failing Tests:**  
**Execution:** Subagent in **code** mode  
**Input Contract:** `reference/red-phase-request-template.md`  
**Output Contract:** `reference/red-phase-response-template.md`  
**Deliverable:** Test files with failing tests

**TDD Red Phase Review:**  
**Custom Role:** Test Reviewer (no Blueprint skill)  
**Execution:** Subagent in **architect** mode (read only)  
**Input Contract:** `reference/test-review-request-template.md`  
**Output Contract:** `reference/test-review-response-template.md`  
**Deliverable:** Test quality assessment, approval or revision request

**Test Reviewer verifies:**
- Tests exist for the current step
- Test descriptions clearly reflect behavior to be implemented
- Tests contain real assertions checking expected behavior (not forced fails like `FAIL()` or `assert(false)`)
- Tests actually fail (red phase confirmed via execution)
- Tests are properly structured and maintainable

**Green Phase - Implement Code:**  
**Blueprint Skill:** `/implement` (per step)  
**Execution:** Subagent in **code** mode  
**Input Contract:** `reference/green-phase-request-template.md`  
**Output Contract:** `reference/green-phase-response-template.md`  
**Deliverable:** Implementation code, passing tests

**Optional Step Review:**  
**Custom Role:** Code Reviewer (no Blueprint skill)  
**Execution:** Subagent in **architect** mode (read only)  
**Input Contract:** `reference/code-review-request-template.md`  
**Output Contract:** `reference/code-review-response-template.md`  
**Deliverable:** `blueprint/context/cooperative/code-review-N.md`

### Steps
1. **Prepare:** Identify next step from `current-feature.md`, verify TDD requirements
2. **Red Phase:** Write failing tests for current step (via `/implement` or manual)
3. **Red Phase Review:** Launch Test Reviewer subagent in **architect** mode to verify test quality and red phase
4. **Green Phase:** Implement code to make tests pass (via `/implement` subagent in **code** mode)
5. **Code Review:** Optionally launch Code Reviewer subagent in **architect** mode using `reviewer-role.md`
6. **Track:** Coordinator updates `current-task-context.md` with evidence, moves to next step
7. **Repeat:** Linear progression through all specification steps

### Requirements
- Clear TDD requirements per step
- Implementation follows project quality gates
- Review frequency based on project configuration
- Progress tracked with evidence in coordinator context

## Phase 4: Quality Gates & Final Acceptance

### Delegation
**Blueprint Skill:** `/check`  
**Execution:** Subagent in **code** mode  
**Input Contract:** `reference/check-request-template.md`  
**Output Contract:** `reference/check-response-template.md`  
**Deliverable:** Behavioral verification report

### Steps
1. **Behavioral Check:** Launch `/check` subagent in **code** mode for behavioral verification against done-when criteria
2. **Full Test Suite:** Coordinator runs complete test suite (e.g., `pio test -e native`) and verifies all tests pass
3. **Deliverables:** Coordinator compiles evidence, updates documentation
4. **Human Gate 2:** Present final acceptance checklist to user with test results, request completion approval

### Requirements
- `/check` behavioral verification passes
- Full test suite executes successfully with all tests green
- No blocking issues in implementation
- Explicit user acceptance recorded in coordinator context

## Phase 5: Documentation Update

### Steps
1. **Documentation Review:** Review changes from `current-feature.md` implementation against `blueprint/context/updatable-docs.md` checklist
2. **Identify Updates:** Determine which documentation files require updates based on:
   - Architecture changes
   - New or modified public interfaces
   - Changed behavior or capabilities
   - Updated coding patterns or standards
3. **Update Documentation:** Launch architect subagent in **architect** mode to update identified documentation files
4. **Validation:** Verify all updated documentation is:
   - Accurate and reflects current implementation
   - Consistent across related documents
   - Indexed and linked in project overview
5. **Record:** Coordinator documents which files were updated in coordinator context

### Requirements
- All relevant documentation updated per `updatable-docs.md` checklist
- Documentation changes committed with feature implementation
- No orphaned or out-of-sync documentation references

## Phase 6: Completion & Cleanup

### Delegation
**Blueprint Skill:** `/complete`  
**Execution:** Subagent in **code** mode  
**Input Contract:** `reference/complete-request-template.md`  
**Output Contract:** `reference/complete-response-template.md`  
**Deliverable:** Work commit, merge (or pull request), archived artifacts in `blueprint/history/`

### Steps
1. **Finalize:** Launch `/complete` subagent in **code** mode to finalize feature, update build plan
2. **Archive Blueprint artifacts:** Coordinator verifies `/complete` moved standard artifacts to `blueprint/history/[features|fixes|rollbacks]/[item].md`
3. **Archive Cooperative context:** Coordinator copies all cooperative-development artifacts to `blueprint/history/[features|fixes|rollbacks]/[item]-cooperative/`:
   - `current-task-context.md` - process metadata and decisions
   - `critic-feedback.md` - specification review results
   - `test-review-*.md` - TDD red phase review results (if any)
   - `code-review-*.md` - step code review results (if any)
   - Any other workflow artifacts from `blueprint/context/cooperative/`
4. **Cleanup:** Reset coordinator context for next task

### Requirements
- `/complete` succeeds before archiving
- All Blueprint standard artifacts preserved in `blueprint/history/`
- All cooperative-development workflow artifacts preserved in `blueprint/history/[item]-cooperative/`
- Provides full audit trail of development process including TDD and review gates
- Clean coordinator state for next cycle

## Available Modes Reference

The following modes from `.harvimodes` are available for subagent execution:

- **architect** - Planning, design, specification work; read + markdown editing only
- **code** - Implementation, testing, verification; full read/write/command access
- **debug** - Troubleshooting and root cause analysis when implementation issues arise
- **orchestrator** - Complex multi-step coordination (not typically used within cooperative flow)
- **project-research** - Deep codebase investigation when context gathering is needed

**Fallback strategies:**
- Use **debug** mode when implementation or verification repeatedly fails
- Use **project-research** mode when subagents lack necessary codebase context

## Project Configuration

### Quality Gates
- Integrate `quality-gates.md` TDD and standards into implementation

### Review Configuration
- Step review frequency from project config
- Independent review for sensitive changes

### Verification Commands
- Use project-specific test/build commands
- Follow Blueprint verification patterns

## Coordinator Responsibilities

### Context Management
- Maintain `blueprint/context/cooperative/current-task-context.md` with process state
- Record decisions and approvals with timestamps
- Preserve execution trace and artifact references
- Keep coordinator context minimal (metadata only)

### Subagent Orchestration
- Launch appropriate Blueprint skills or custom roles in correct modes
- Provide complete, focused context to each subagent
- Process subagent outputs and update coordinator state
- Handle subagent failures with retry/fallback strategy

### Human Gates
- Present clear, actionable information for decision points
- Stop execution at specified gates (specification approval, final acceptance)
- Record explicit user approvals with timestamps in coordinator context
- Never bypass human gates or assume approval

## Constraints & Requirements

### Process Constraints
1. **Linear:** Sequential steps, no parallel work within a phase
2. **Two Gates:** Only specification approval (Gate 1) and final acceptance (Gate 2)
3. **No Autopilot:** Does not run `/autopilot`; each phase executed explicitly via subagents
4. **Separate Reviewers:** Critic and Reviewer are isolated subagents in **architect** mode
5. **Subagent Isolation:** Each subagent receives minimal focused context, results preserved in files

### Quality Requirements
1. **TDD Compliance:** All implementation steps follow red/green/refactor via `/implement` subagents
2. **Quality Gates:** Project standards enforced through `/check` and `/audit` subagents
3. **Evidence-Based:** Verification documented per step in coordinator context
4. **Audit Trail:** Decisions and approvals recorded with timestamps

### Technical Requirements
1. **Blueprint Integration:** Uses `/feature`, `/implement`, `/check`, `/audit`, `/complete` as subagents
2. **Context Preservation:** All artifacts stored in repository files, not coordinator memory
3. **Project Configuration:** Respects quality gates and review settings from `blueprint/config.json`
4. **Mode Discipline:** Correct mode selection for each subagent (architect vs code vs debug)

## Usage

### Starting a Task
```bash
# For build plan item
/cooperative item 2

# For new feature  
/cooperative "Feature description"

# For bug fix
/cooperative fix "Bug description"
```

### Human Gate Points
1. **After specification review:** Approve specification and checklist
2. **After quality gates:** Complete final acceptance checklist

### Monitoring Progress
- Check `current-task-context.md` for current status
- Review `critic-feedback.md` and `reviewer-report-*.md` for assessments
- Monitor `review.md` and `findings.md` for blockers

---

*Based on practical testing with real cooperative development workflow. Incorporates template-based coordination and evidence-driven validation.*
---
name: cooperative-development
description: Linear automated development workflow with two human gates for specification approval and final acceptance.
---

# Cooperative Development (Linear Conveyor)

**Purpose:** Linear sequence of validated steps with two human gates: specification approval and final acceptance.

**Process:** Specification → Critic Review → Human Gate 1 → Implementation → Quality Gates → Human Gate 2 → Completion

**Human Gates:** (1) Specification approval, (2) Final acceptance

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
- `/check` and `/audit` per project configuration
- **HUMAN GATE:** User completes final acceptance checklist

### 5. Completion
- `/complete` after acceptance
- Archive context and artifacts

## Phase 1: Specification Preparation

### Steps
1. **Context:** Create `blueprint/context/cooperative/current-task-context.md`
2. **Specification:** `/feature` or `/fix` creates `current-feature.md` with acceptance checklist
3. **Validation:** Ensure quality gates integrated, no blocking ambiguities

### Requirements
- Complete, actionable specification
- Acceptance checklist for human gates
- Quality gates integrated into specification
- No architectural blockers

## Phase 2: Specification Review & Approval

### Steps
1. **Critic Review:** Separate subagent reviews specification via `critic-role.md`
2. **Feedback:** Critic creates `critic-feedback.md` with P1/P2/P3 findings
3. **Blockers:** Resolve P1 issues via architect revision if needed
4. **Human Gate 1:** User approves specification and checklist

### Requirements
- Critic separate from specification author
- All P1 issues resolved before approval
- Explicit user approval recorded in task context

## Phase 3: Linear Implementation

### Steps
1. **Prepare:** Identify step from `current-feature.md`, verify TDD requirements
2. **Implement:** Developer executes step via `/implement` approach, TDD red phase continues
3. **Review:** Based on config, reviewer subagent assesses using `reviewer-role.md`
4. **Track:** Update `current-task-context.md` with evidence, move to next step
5. **Repeat:** Linear progression through all specification steps

### Requirements
- Clear TDD requirements per step
- Implementation follows project quality gates
- Review frequency based on project configuration
- Progress tracked with evidence

## Phase 4: Quality Gates & Final Acceptance

### Steps
1. **Checks:** `/check` for behavioral verification, project tests
2. **Review:** `/audit` for quality, resolve blockers in `review.md`/`findings.md`
3. **Deliverables:** Compile evidence, update documentation
4. **Human Gate 2:** User completes final acceptance checklist

### Requirements
- All automated checks pass
- No P1 issues in `review.md` or `findings.md`
- Explicit user acceptance recorded

## Phase 5: Completion & Cleanup

### Steps
1. **Finalize:** `/complete` feature, update build plan
2. **Archive:** Move context to archive, preserve artifacts
3. **Cleanup:** Reset for next task

### Requirements
- `/complete` succeeds before archiving
- Artifacts preserved for audit
- Clean state for next cycle

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

### Context
- Maintain `current-task-context.md`
- Record decisions and approvals
- Preserve evidence

### Human Gates
- Present clear information for decisions
- Stop at specified gates
- Record explicit approvals

### Subagents
- Launch appropriate roles
- Provide complete context
- Process outputs

## Constraints & Requirements

### Process Constraints
1. **Linear:** Sequential steps, no parallel work
2. **Two Gates:** Only specification approval and final acceptance
3. **No Autopilot:** Does not run `/autopilot` by default
4. **Separate Reviewers:** Critic and reviewer separate subagents

### Quality Requirements
1. **TDD Compliance:** All steps follow red/green/refactor
2. **Quality Gates:** Project standards enforced
3. **Evidence-Based:** Verification documented per step
4. **Audit Trail:** Decisions and approvals recorded

### Technical Requirements
1. **Blueprint Integration:** Uses `/feature`, `/implement`, `/check`, `/complete`
2. **Context Preservation:** Artifacts in repository
3. **Project Configuration:** Respects quality gates and review settings

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
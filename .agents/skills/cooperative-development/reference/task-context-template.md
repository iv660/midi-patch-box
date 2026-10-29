# Task Context Template

**File:** `blueprint/context/cooperative/current-task-context.md`  
**Maintained by:** Coordinator  
**Used by:** All agents for context and status

## Purpose
Centralized document for tracking cooperative development task progress, agent assignments, decisions, and workflow state.

## Template Structure

```markdown
# Current Task Context

## Task Information

**Task ID:** [CD-###]  
**Start Date:** [YYYY-MM-DD]  
**Coordinator:** [Coordinator name]  
**Status:** [Current phase and status]

## Task Description

**Source:** [Build Plan Item #X / Ad-hoc task]  
**Title:** [Task title]  
**Description:** [Brief task description]

## Project Context

**Project:** [Project name]  
**Technology:** [Primary technology stack]  
**Architecture:** [Key architectural patterns]  
**Current State:** [Current project state relevant to task]

## Workflow Progress

### Phase 1: Architectural Specification
- [ ] Task received from user
- [ ] Architect assigned
- [ ] Specification created (v1.0)
- [ ] Feature branch created: `[branch-name]`
- [ ] Critic review completed
- [ ] Architect revision requested
- [ ] Specification revised (v2.0)
- [ ] Critic re-review - [APPROVED/NEEDS REVISION]
- [ ] User approval obtained ([YYYY-MM-DD])

### Phase 1: Quality Gate Compliance Review (Optional)
- [ ] Fresh critic review for quality gate compliance
- [ ] Quality gate violations identified:
  1. [Violation 1 (P1/P2)]
  2. [Violation 2 (P1/P2)]
- [ ] Revision request #[number] created
- [ ] Architect revision completed - Specification v[number].0 created
- [ ] Quality gate compliance achieved:
  1. ✅ [Violation 1 resolved]
  2. ✅ [Violation 2 resolved]
- [ ] Quality Gate Compliance: ✅ FULLY COMPLIANT
- [ ] User re-approval [pending/obtained]

### Phase 2: Iterative Implementation
- [ ] Step 1: [Step description]
- [ ] Step 1 committed to feature branch ([commit-hash])
- [ ] Step 1 review by Reviewer
- [ ] Step 2: [Step description]
- [ ] Step 2 review by Reviewer
- [ ] [Continue for all steps...]

### Phase 3: Final Verification
- [ ] All tests pass ([test command])
- [ ] Build succeeds for all targets
- [ ] Blueprint check completed
- [ ] User acceptance obtained

## Agent Assignments

- **Architect:** [Status] ([Specification version])
- **Critic:** [Status] ([Review outcome])
- **Developer:** [Status] ([Current step])
- **Reviewer:** [Status] ([Current review])
- **Coordinator:** [Current activity]

## Decision Log

### [YYYY-MM-DD]
- [Decision/event 1]
- [Decision/event 2]

### [YYYY-MM-DD] ([Phase] - [Activity])
- [Detailed activity log 1]
- [Detailed activity log 2]
- [Key decisions made]

## Notes

[Any additional notes, observations, or context for the task]
```

## Usage Instructions

### For Coordinator:
1. Create this file at task initiation: `blueprint/context/cooperative/current-task-context.md`
2. Update after each significant workflow event
3. Maintain accurate agent assignments and status
4. Add decision log entries for audit trail
5. Commit changes regularly to preserve history

### For Other Agents:
1. Read this file to understand task context and current state
2. Check agent assignments before starting work
3. Review decision log for historical context
4. Update your status through coordinator when work completes

## File Naming Convention

- **Current context:** `current-task-context.md`
- **Archived contexts:** `task-context-[task-id]-[date].md`
- **Related files:** Store in same `cooperative` directory

## Update Triggers

Update this file when:

1. **Task initiation:** Fill initial template
2. **Agent assignment:** Update Agent Assignments section
3. **Phase transition:** Update Workflow Progress
4. **Significant decision:** Add to Decision Log
5. **Status change:** Update Status and relevant sections
6. **Completion:** Mark all relevant items complete

## Example Sections

### Agent Status Indicators:
- ✅ **Completed** ([details])
- 🚀 **In progress** ([activity])
- ⏳ **Awaiting** ([dependency])
- ❌ **Blocked** ([blocker])

### Phase Status:
- **Phase 1:** Architectural Specification
- **Phase 2:** Iterative Implementation
- **Phase 3:** Final Verification

### Decision Log Format:
```
### YYYY-MM-DD (Phase - Activity)
- [Bullet point describing event/decision]
- [Include commit hashes, file references, agent actions]
```

## Best Practices

1. **Keep Current:** Update within same working session as events occur
2. **Be Specific:** Include commit hashes, file paths, version numbers
3. **Maintain Consistency:** Use same status indicators throughout
4. **Document Decisions:** Every significant choice should be in Decision Log
5. **Reference Files:** Link to related documents (specs, reviews, reports)
6. **Regular Commits:** Commit updates to preserve timeline

## Integration with Other Files

This file references and is referenced by:

- **Review requests:** `review-request-###.md`
- **Reviewer reports:** `reviewer-report-###-actual.md`
- **Architectural specs:** `architect-output.md`, `architect-decisions-###.md`
- **Critic feedback:** `critic-feedback.md`, `revision-request-###.md`
- **Quality gates:** `quality-gates.md`
- **Feature spec:** `current-feature.md`
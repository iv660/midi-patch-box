# Critic Role

**Purpose:** Review architectural decisions and specifications for compliance with project standards and requirements.

## Inputs from Coordinator

The critic receives:
1. **Architect's specification** - `current-feature.md` or equivalent
2. **Architectural notes** - Decisions and rationale from architect
3. **Project standards** - References to coding standards and architecture docs
4. **Task requirements** - Original task description

## Responsibilities

1. **Standards Compliance** - Check adherence to project architecture patterns
2. **Completeness Review** - Ensure specification covers all requirements
3. **Feasibility Assessment** - Evaluate technical feasibility of the approach
4. **Risk Identification** - Identify potential risks or issues
5. **Alternative Consideration** - Suggest alternatives if appropriate

## Review Criteria

### Architecture Compliance
- Follows State pattern architecture (if applicable)
- Maintains DI container and interface design
- Ensures testability through native target
- Follows TDD development approach
- Uses unified menu interaction patterns

### Specification Quality
- Clear, testable done-when criteria
- Appropriate step breakdown
- Complete coverage of requirements
- Realistic implementation estimates
- Proper consideration of edge cases

### Integration Points
- Correct identification of affected components
- Appropriate use of existing interfaces
- Minimal disruption to existing functionality
- Proper consideration of backward compatibility

## Work Process

1. Read the architect's specification and notes
2. Review relevant project documentation (ARCHITECTURE.md, coding-standards.md)
3. Analyze the proposed solution against project patterns
4. Identify any gaps, inconsistencies, or risks
5. Provide structured feedback with specific issues

## Outputs to Coordinator

The critic returns:
1. **Review findings** - Structured feedback on the specification
2. **Compliance status** - Overall assessment of standards compliance
3. **Specific issues** - List of issues requiring attention
4. **Recommendations** - Suggested improvements or alternatives
5. **Approval status** - Whether the specification is ready for next phase

## Feedback Template

When reporting back to coordinator:

```
## Critic Review for: [Task Name]

**Overall assessment:** [Approved/Needs Revision/Rejected]

**Standards compliance:**
- [✓/✗] Architecture patterns followed
- [✓/✗] DI and interfaces maintained
- [✓/✗] Testability considered
- [✓/✗] TDD approach supported

**Issues identified:**
1. **P1: [Critical issue]** - [Description and impact]
   - Suggestion: [Recommended fix]

2. **P2: [Major issue]** - [Description and impact]
   - Suggestion: [Recommended fix]

3. **P3: [Minor issue]** - [Description]
   - Suggestion: [Optional improvement]

**Missing elements:**
- [Element 1 that should be included]
- [Element 2 that should be included]

**Risk assessment:**
- [Risk 1] - [Likelihood and impact]
- [Risk 2] - [Likelihood and impact]

**Recommendations:**
1. [Primary recommendation]
2. [Secondary recommendation]

**Next steps:**
- [ ] Address P1 issues before proceeding
- [ ] Consider P2 suggestions for improvement
- [ ] Optional: Review P3 items
```

---

*This role description will be refined through practical use in the cooperative development workflow.*
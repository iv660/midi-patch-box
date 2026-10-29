# Reviewer Role

**Purpose:** Perform technical code review of implementation steps, ensuring quality and adherence to specifications.

## Inputs from Coordinator

The reviewer receives:
1. **Implementation step** - Code changes from developer for a specific step
2. **Specification requirements** - Relevant part of `current-feature.md`
3. **Project standards** - Coding standards and architecture documentation
4. **Context** - Previous steps and overall implementation plan

## Responsibilities

1. **Code Quality Review** - Check adherence to coding standards
2. **Specification Compliance** - Verify implementation matches requirements
3. **Architecture Consistency** - Ensure alignment with project architecture
4. **Test Adequacy** - Review test coverage and quality
5. **Integration Check** - Verify proper integration with existing code
6. **Performance/Security** - Identify potential issues (if applicable)

## Review Focus Areas

### Code Standards
- Follows project coding standards
- Consistent naming conventions
- Proper comments and documentation
- Appropriate error handling
- Memory management (for C++)

### Architecture Compliance
- Maintains State pattern architecture
- Preserves DI container and interface design
- Ensures testability through native target
- Follows TDD development approach
- Uses unified menu interaction patterns

### Specification Alignment
- Implements exactly what was specified
- No scope creep or unnecessary features
- Proper handling of edge cases
- Meets done-when criteria for the step

### Testing Quality
- Tests cover specified functionality
- Tests follow TDD approach
- Test names are descriptive
- Edge cases are tested
- Tests are maintainable

## Work Process

1. Examine the code diff provided by developer
2. Review against the specification requirements for this step
3. Check adherence to project standards and patterns
4. Analyze test coverage and quality
5. Run any relevant verification commands if needed
6. Provide structured, actionable feedback

## Outputs to Coordinator

The reviewer returns:
1. **Review findings** - Structured feedback on the implementation
2. **Approval status** - Approved/Needs Revision/Rejected
3. **Specific issues** - List of issues categorized by severity
4. **Recommendations** - Suggested improvements
5. **Risk assessment** - Any identified risks

## Feedback Template

When reporting back to coordinator:

```
## Reviewer Report for Step: [Step Number/Description]

**Overall assessment:** [Approved/Needs Revision/Rejected]

**Code quality review:**
- [✓/✗] Coding standards followed
- [✓/✗] Naming conventions consistent
- [✓/✗] Comments and documentation adequate
- [✓/✗] Error handling appropriate

**Architecture compliance:**
- [✓/✗] State pattern maintained
- [✓/✗] DI and interfaces preserved
- [✓/✗] Testability ensured
- [✓/✗] TDD approach followed

**Specification alignment:**
- [✓/✗] Implements specified requirements
- [✓/✗] No scope creep
- [✓/✗] Edge cases handled
- [✓/✗] Done-when criteria met

**Testing review:**
- [✓/✗] Tests cover functionality
- [✓/✗] Test names descriptive
- [✓/✗] Edge cases tested
- [✓/✗] Tests maintainable

**Issues identified:**

**P1: Critical issues (must be fixed)**
1. [Issue description]
   - Impact: [What's wrong]
   - Suggestion: [How to fix]
   - Location: [File:line]

**P2: Major issues (should be fixed)**
1. [Issue description]
   - Impact: [What's wrong]
   - Suggestion: [How to fix]
   - Location: [File:line]

**P3: Minor issues (optional improvements)**
1. [Issue description]
   - Suggestion: [Improvement]
   - Location: [File:line]

**Risk assessment:**
- [Risk 1] - [Likelihood and impact]
- [Risk 2] - [Likelihood and impact]

**Verification performed:**
- [✓/✗] Tests pass: [Command and result]
- [✓/✗] Build passes: [Command and result]
- [✓/✗] Other verification: [What was checked]

**Next steps:**
- [ ] Address P1 issues before proceeding
- [ ] Consider P2 suggestions
- [ ] Optional: Review P3 improvements
```

## Integration with Blueprint

The reviewer may use aspects of Blueprint `/audit` skill, focusing on:
- Code quality and standards compliance
- Architecture consistency
- Test adequacy
- Specification alignment

---

*This role description will be refined through practical use in the cooperative development workflow.*
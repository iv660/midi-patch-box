# QA Engineer Role

**Purpose:** Create acceptance tests based on specifications and run final verification of implementation.

## Inputs from Coordinator

The QA engineer receives:
1. **Approved specification** - `current-feature.md` after architect and critic review
2. **Project context** - Test infrastructure and existing test patterns
3. **Quality requirements** - Any specific testing requirements or constraints

## Responsibilities

1. **Test Planning** - Design acceptance test strategy based on specification
2. **Test Creation** - Create acceptance tests that verify done-when criteria
3. **Test Infrastructure** - Ensure tests can be executed within project framework
4. **Final Verification** - Run acceptance tests on completed implementation
5. **Quality Reporting** - Report test results and any issues found

## Work Process

### Test Creation Phase (parallel with development)
1. Analyze specification and identify acceptance criteria
2. Design test cases that verify each done-when criterion
3. Create test implementations following project test patterns
4. Ensure tests are independent and repeatable
5. Document test approach and coverage

### Final Verification Phase (after implementation)
1. Run acceptance test suite on completed implementation
2. Record test results and any failures
3. Identify discrepancies between specification and implementation
4. Report issues back to coordinator for resolution

## Test Types for Embedded C++ Project

### Unit Tests
- Test individual components in isolation
- Use Unity test framework with PlatformIO
- Follow existing test patterns in `test/` directory

### Integration Tests
- Test interactions between components
- Verify integration points work correctly
- Use mock objects where appropriate

### Acceptance Tests
- Verify end-to-end functionality matches specification
- Test user-facing behavior and scenarios
- May involve hardware simulation for embedded project

## Outputs to Coordinator

The QA engineer returns:
1. **Acceptance test suite** - Test files implementing verification
2. **Test plan** - Documentation of test approach and coverage
3. **Test execution results** - Results from running tests on implementation
4. **Quality assessment** - Overall assessment of implementation quality
5. **Issues found** - Any discrepancies or problems identified

## Integration with Project Testing

For PlatformIO C++ project:
- Tests placed in appropriate `test/` subdirectory
- Use `pio test -e native` for unit tests
- Follow existing test patterns and naming conventions
- Ensure tests work with project build system

## Communication Template

When reporting back to coordinator:

```
## QA Engineer Report for Task: [Task Name]

**Test planning complete:** [Date]

**Acceptance test coverage:**
- [✓/✗] Done-when criterion 1: [Test coverage description]
- [✓/✗] Done-when criterion 2: [Test coverage description]
- [✓/✗] Done-when criterion 3: [Test coverage description]

**Test infrastructure:**
- Tests located: [Directory path]
- Test command: [Command to run tests]
- Execution environment: [Native/hardware simulation]

**Test execution results (final verification):**
- Total tests: [Number]
- Passed: [Number]
- Failed: [Number]
- Execution time: [Time]

**Issues identified during verification:**

**Critical issues (blocking acceptance):**
1. [Issue description]
   - Test that failed: [Test name]
   - Expected: [Expected behavior]
   - Actual: [Actual behavior]
   - Impact: [Why it's critical]

**Major issues (should be fixed):**
1. [Issue description]
   - Test that failed: [Test name]
   - Expected: [Expected behavior]
   - Actual: [Actual behavior]
   - Impact: [Why it's important]

**Minor issues (optional improvements):**
1. [Issue description]
   - Observation: [What was noted]
   - Suggestion: [Optional improvement]

**Overall quality assessment:**
- [✓/✗] All acceptance criteria met
- [✓/✗] Implementation matches specification
- [✓/✗] Code quality acceptable
- [✓/✗] Ready for user acceptance

**Recommendations:**
1. [Primary recommendation]
2. [Secondary recommendation]

**Next steps:**
- [ ] Address critical issues
- [ ] Review major issues
- [ ] Consider minor improvements
```

## Quality Gates

The QA engineer enforces:
- All done-when criteria must have corresponding tests
- Tests must pass on completed implementation
- Implementation must match specification
- Code must meet project quality standards

---

*This role description will be refined through practical use in the cooperative development workflow.*
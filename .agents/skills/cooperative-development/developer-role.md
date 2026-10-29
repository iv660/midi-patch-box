# Developer Role

**Purpose:** Implement code according to specifications, following project standards and practices.

## Inputs from Coordinator

The developer receives:
1. **Approved specification** - `current-feature.md` after architect and critic review
2. **Current implementation step** - Which step to implement (if multi-step)
3. **Project context** - Relevant code files and documentation
4. **Implementation constraints** - Any specific technical constraints

## Responsibilities

1. **Step Implementation** - Implement one specification step at a time
2. **Code Quality** - Follow project coding standards and patterns
3. **Testing** - Write tests as required by specification and project standards
4. **Integration** - Ensure proper integration with existing code
5. **Documentation** - Update code comments and documentation as needed

## Work Process

### Single-Step Implementation
1. Read the specification and understand requirements
2. Analyze existing code to identify integration points
3. Implement the solution following TDD approach
4. Write tests to verify functionality
5. Ensure code follows project standards
6. Run verification commands (build, tests)

### Multi-Step Implementation
1. Receive specific step from coordinator
2. Focus only on that step's requirements
3. Implement incrementally
4. Maintain compatibility with previous steps
5. Report completion back to coordinator

## Integration with Blueprint

The developer uses the standard Blueprint `/implement` skill, either:
- Directly via `new_task` with mode `code`
- By following the implement skill instructions manually
- Working on the feature branch created by the coordinator

## Outputs to Coordinator

The developer returns:
1. **Implementation status** - Completed step or overall progress
2. **Code changes** - Git diff or list of modified files
3. **Test results** - Verification and test execution results
4. **Issues encountered** - Any problems or blockers
5. **Ready for review** - Whether the implementation is ready for reviewer

## Quality Requirements

The developer must ensure:
- **State pattern architecture** is preserved
- **DI container and interface design** is maintained
- **Testability through native target** is ensured
- **TDD development approach** is followed
- **Documentation** is kept up to date
- **Unified menu interaction patterns** are used where applicable

## Communication Template

When reporting back to coordinator:

```
## Developer Report for Step: [Step Number/Description]

**Step implemented:** [Brief description of what was implemented]

**Files modified:**
- [File 1] - [What changed]
- [File 2] - [What changed]

**Tests added/updated:**
- [Test file 1] - [What tests cover]
- [Test file 2] - [What tests cover]

**Verification results:**
- Build: [Passed/Failed]
- Tests: [Passed/Failed/Not applicable]
- Specific verification: [Results of any additional checks]

**Issues encountered:**
- [Issue 1] - [How resolved or if blocking]
- [Issue 2] - [How resolved or if blocking]

**Dependencies on other steps:** [If any]

**Ready for reviewer:** Yes/No

**Next recommended step:** [If multi-step implementation]
```

## TDD Approach

For embedded C++ project with PlatformIO:
1. Write test in `test/` directory following existing patterns
2. Run `pio test -e native` to verify test fails
3. Implement minimal code to make test pass
4. Refactor while keeping tests passing
5. Run full test suite to ensure no regressions

---

*This role description will be refined through practical use in the cooperative development workflow.*
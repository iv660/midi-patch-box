# Quality Gates - MIDI Patch Box

This file defines quality standards that must be met by all architectural specifications, implementation plans, and code changes in the MIDI Patch Box project.

These gates are checked by:
- **Architect** when creating specifications
- **Critic** when reviewing architectural decisions
- **Developer** when implementing features
- **QA Engineer** when creating acceptance tests
- **Reviewer** when reviewing implementation steps

## Development Methodology Gates

### TDD (Test-Driven Development)
- [ ] **Red Phase Verification**: Each implementation step must start with failing tests that are verified to fail before implementation
- [ ] **Test Failure Confirmation**: Red phase completion requires running tests and confirming they fail as expected
- [ ] **Test Commands Defined**: PlatformIO test commands specified for each component
- [ ] **Test Coverage**: Test scenarios cover all functionality and edge cases
- [ ] **All Tests Pass**: All existing tests must pass after each implementation step

### Build Verification
- [ ] **Dual Target Compilation**: Build must succeed for both `native` (tests) and `pico` (target) environments
- [ ] **No Regression**: No regression in existing functionality
- [ ] **Build Commands**: Specific build commands documented in plan
- [ ] **PlatformIO Integration**: Uses proper PlatformIO commands for build/test

## Architectural Quality Gates

### State Pattern Compliance
- [ ] **State Architecture Preserved**: Maintains State pattern design
- [ ] **DI Container Usage**: Uses dependency injection through DI container
- [ ] **Interface-Based Design**: Follows interface contracts for testability
- [ ] **Separation of Concerns**: Clear separation between state logic and view rendering

### Code Quality Standards
- [ ] **Backward Compatibility**: Considered for all interface changes
- [ ] **Error Handling**: Edge cases and error scenarios addressed
- [ ] **Documentation**: Code changes accompanied by documentation updates
- [ ] **Code Review Ready**: Changes are structured for reviewability

## Specification Quality Gates

### Architectural Specifications (Architect Output)
- [ ] **TDD Steps Included**: Each build step includes testing approach
- [ ] **Test Strategy Defined**: Clear unit testing strategy for all components
- [ ] **Quality Criteria**: Done-when criteria include quality checks
- [ ] **Risk Assessment**: Identifies and mitigates technical risks

### Implementation Plans
- [ ] **Incremental Steps**: Small, verifiable implementation steps
- [ ] **Verification Points**: Clear verification criteria for each step
- [ ] **Rollback Considerations**: Plan for reverting changes if needed
- [ ] **Integration Points**: Identifies dependencies and integration requirements

## Project-Specific Requirements

### MIDI Patch Box Standards
- [ ] **Hardware Compatibility**: Changes work with actual hardware constraints
- [ ] **Real-time Considerations**: Respects embedded system real-time requirements
- [ ] **Memory Constraints**: Considers limited memory on target device
- [ ] **Display Limitations**: Works within physical display constraints

### Menu Subsystem Standards
- [ ] **Consistent Navigation**: Uniform menu navigation patterns
- [ ] **State Transitions**: Proper state machine transitions
- [ ] **User Experience**: Maintains consistent user interaction patterns
- [ ] **View Abstraction**: Proper separation between state and view layers

## Quality Gate Checklist Template

Copy this template into specifications and plans to track quality gate compliance:

```markdown
### Quality Gate Compliance

**Development Methodology:**
- [ ] TDD Red Phase included for each step
- [ ] Test commands specified: `pio test -e native -f [test_name]`
- [ ] All existing tests pass after step
- [ ] Build succeeds for native and pico targets

**Architectural Compliance:**
- [ ] State pattern maintained
- [ ] DI container used properly
- [ ] Interface contracts followed
- [ ] Backward compatibility considered

**Project Standards:**
- [ ] Hardware constraints respected
- [ ] Memory usage considered
- [ ] Real-time requirements met
- [ ] Display limitations addressed
```

## How to Use These Gates

### For Architects
1. Include quality gate checklist in specifications
2. Document how each gate will be met
3. Address project-specific requirements explicitly
4. Update `current-feature.md` with quality criteria

### For Critics
1. Review specifications against all quality gates
2. Mark compliance in feedback report
3. Identify missing quality considerations as P1/P2/P3 issues
4. Require quality gate updates in revision requests

### For Developers
1. **Red Phase Verification**: Create failing test first, then run test command to confirm it fails
2. **TDD Cycle**: Red (test fails) → Green (implement to pass test) → Refactor (improve while tests pass)
3. Verify quality gates at each implementation step
4. Run all tests and builds before marking step complete
5. Document test failure confirmation in red phase reports
6. Document quality verification in implementation reports

### For Coordinators
1. Include `quality-gates.md` in context for all agents
2. Verify quality gates are checked during reviews
3. Escalate quality gate violations as critical issues
4. Track quality compliance across workflow phases

---

*Last updated: 2026-10-24*  
*Project: MIDI Patch Box - Embedded C++ with PlatformIO*
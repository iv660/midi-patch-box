# Test-Driven Development (TDD) Guide

This guide demonstrates practical TDD implementation based on the State Machine refactoring performed in this project.

## Core TDD Principles

**Red-Green-Refactor Cycle:**
1. **Red**: Write a complete, failing test for one specific functionality
2. **Green**: Write minimal code to make that test pass
3. **Refactor**: Improve code quality while keeping tests green

**Critical Rule**: Complete the full RGR cycle for each test method individually. Never move to the next test until the current one is fully working.

## Red Phase Requirements

The Red phase test must be:
- **Complete and final** - written as if the implementation already exists
- **Failing due to missing implementation** - not artificial FAIL() calls
- **Testing real behavior** - verifying actual functionality, not test infrastructure

**Example of proper Red phase**:
```cpp
void testShouldCallEnterOnStateChange(void) {
    StateMachine stateMachine;
    MockState* mockState = new MockState();
    
    stateMachine.changeState(mockState);  // This will fail - method doesn't exist yet
    
    TEST_ASSERT_TRUE(mockState->enterWasCalled());
}
```

## Implementation-First Approach

**Test implementations, not interfaces**. Interfaces are design tools - we test the concrete classes that implement them.

**Correct approach**:
```cpp
// Test the concrete implementation
void testSplashScreenStateShowsMessageOnEnter(void) {
    MockSplashScreenView mockView;
    SplashScreenState state(&mockView);  // Testing concrete class
    
    state.enter();
    
    TEST_ASSERT_TRUE(mockView.showMessageWasCalled());
}
```

## TDD Workflow Example

### Step 1: Write One Red Test
```cpp
void testStateMachineCanChangeState(void) {
    StateMachine stateMachine;
    MockState* mockState = new MockState();
    
    stateMachine.changeState(mockState);  // Compilation fails - method missing
    
    TEST_ASSERT_TRUE(mockState->enterWasCalled());
}
```

### Step 2: Make It Compile (Green)
```cpp
// StateMachine.h
class StateMachine {
public:
    void changeState(State* newState) {
        // Minimal implementation
        if (newState) {
            newState->enter();
        }
    }
};
```

### Step 3: Refactor If Needed
```cpp
// Improve code structure while keeping test green
class StateMachine {
private:
    State* currentState = nullptr;
    
    bool hasCurrentState() const {
        return currentState != nullptr;
    }
    
public:
    void changeState(State* newState) {
        if (hasCurrentState()) {
            currentState->exit();
        }
    }
};
```

### Step 4: Move to Next Test
Only after the first test is completely working, write the next test:

```cpp
void testStateMachineCallsExitOnPreviousState(void) {
    StateMachine stateMachine;
    MockState* firstState = new MockState();
    MockState* secondState = new MockState();
    
    stateMachine.changeState(firstState);
    stateMachine.changeState(secondState);
    
    TEST_ASSERT_TRUE(firstState->exitWasCalled());
}
```

## Mock Object Pattern

Keep mocks simple and focused:

```cpp
class MockState : public State {
private:
    bool enterCalled = false;
    bool exitCalled = false;
    bool updateCalled = false;

public:
    void enter() override { enterCalled = true; }
    void exit() override { exitCalled = true; }
    void update() override { updateCalled = true; }

    bool enterWasCalled() const { return enterCalled; }
    bool exitWasCalled() const { return exitCalled; }
    bool updateWasCalled() const { return updateCalled; }
};
```

## Test Structure

```cpp
void testShouldDoSpecificBehaviorWhenCondition(void) {
    // Arrange - Set up test data and mocks
    MockDependency mockDep;
    ComponentUnderTest component(&mockDep);
    
    // Act - Execute the behavior being tested
    component.performAction();
    
    // Assert - Verify expected outcomes
    TEST_ASSERT_TRUE(mockDep.expectedMethodWasCalled());
}
```

## Key Rules

1. **One test at a time** - Complete RGR cycle before moving to next test
2. **Red phase must be real** - Test should fail due to missing implementation, not artificial failures
3. **Test implementations** - Focus on concrete classes, not abstract interfaces
4. **Minimal Green** - Write just enough code to make the test pass
5. **Refactor fearlessly** - Improve code while keeping tests green

## Running Tests

```bash
# Run all tests
pio test -e native

# Run specific test suite
pio test -e native -f test_state_machine
```

This disciplined TDD approach ensures robust, well-tested code that can be refactored with confidence.
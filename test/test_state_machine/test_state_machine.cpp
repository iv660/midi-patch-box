#include "unity.h"
#include "app/StateMachine.h"
#include "app/State.h"

// Mock State for testing
class MockState : public State {
private:
    bool enterCalled = false;
    bool updateCalled = false;
    bool exitCalled = false;

public:
    void enter() override {
        enterCalled = true;
    }

    void update() override {
        updateCalled = true;
    }

    void exit() override {
        exitCalled = true;
    }

    bool enterWasCalled() const { return enterCalled; }
    bool updateWasCalled() const { return updateCalled; }
    bool exitWasCalled() const { return exitCalled; }
};

void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

void testStateMachineCanChangeState(void) {
    StateMachine stateMachine;
    MockState* mockState = new MockState();
    
    stateMachine.changeState(mockState);
    
    TEST_ASSERT_TRUE(mockState->enterWasCalled());
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(testStateMachineCanChangeState);
    
    return UNITY_END();
}
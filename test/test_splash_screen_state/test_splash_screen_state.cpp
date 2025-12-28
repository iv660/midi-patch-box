#include "unity.h"
#include "app/SplashScreenState.h"
#include "app/SplashScreenViewInterface.h"
#include "app/StateMachine.h"
#include "app/StateMachineInterface.h"
#include "app/MainApplicationState.h"
#include "app/StateFactoryInterface.h"
#include "mocks/MockIoDriver.h"
#include <typeinfo>

// Mock SplashScreenView for testing
class MockSplashScreenView : public SplashScreenViewInterface {
private:
    bool showMessageCalled = false;
    bool hideCalled = false;

public:
    void showMessage() override {
        showMessageCalled = true;
    }

    void hide() override {
        hideCalled = true;
    }

    bool showMessageWasCalled() const { return showMessageCalled; }
    bool hideWasCalled() const { return hideCalled; }
};

// Mock StateFactory for testing
class MockStateFactory : public StateFactoryInterface {
private:
    bool createMainApplicationStateCalled = false;

public:
    StateInterface* createMainApplicationState() override {
        createMainApplicationStateCalled = true;
        return nullptr; // Return nullptr for testing - we only care about the call
    }

    bool createMainApplicationStateWasCalled() const {
        return createMainApplicationStateCalled;
    }
};

// Mock StateMachine for testing transitions
class MockStateMachine : public StateMachineInterface {
private:
    bool changeStateCalled = false;

public:
    void changeState(StateInterface* newState) override {
        changeStateCalled = true;
        // Don't actually change state in test - just track the call
        if (newState) {
            delete newState; // Clean up to avoid memory leak
        }
    }

    void update() override {
        // Empty implementation for testing
    }

    bool changeStateWasCalled() const {
        return changeStateCalled;
    }
};

void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

void testSplashScreenStateShowsMessageOnEnter(void) {
    MockSplashScreenView mockView;
    MockIoDriver mockIoDriver;
    MockStateFactory mockFactory;
    SplashScreenState splashState(&mockView, &mockIoDriver, &mockFactory);
    
    splashState.enter();
    
    TEST_ASSERT_TRUE(mockView.showMessageWasCalled());
}

void testSplashScreenStateTransitionsAfterOneSecond(void) {
    MockSplashScreenView mockView;
    MockIoDriver mockIoDriver;
    MockStateFactory mockFactory;
    MockStateMachine mockStateMachine;
    SplashScreenState splashState(&mockView, &mockIoDriver, &mockFactory);
    
    // Inject mock state machine
    splashState.setStateMachine(&mockStateMachine);
    
    // Enter the state to start timer
    mockIoDriver.resetTime();
    splashState.enter();
    
    // Simulate time passing - less than 1 second should not trigger transition
    mockIoDriver.delay(999);
    splashState.update();
    TEST_ASSERT_FALSE(mockFactory.createMainApplicationStateWasCalled());
    TEST_ASSERT_FALSE(mockStateMachine.changeStateWasCalled());
    
    // Simulate 1 more millisecond to reach 1000ms total
    mockIoDriver.delay(1);
    splashState.update();
    TEST_ASSERT_TRUE(mockFactory.createMainApplicationStateWasCalled());
    TEST_ASSERT_TRUE(mockStateMachine.changeStateWasCalled());
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(testSplashScreenStateShowsMessageOnEnter);
    RUN_TEST(testSplashScreenStateTransitionsAfterOneSecond);
    
    return UNITY_END();
}
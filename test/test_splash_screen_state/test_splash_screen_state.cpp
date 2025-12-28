#include "unity.h"
#include "app/SplashScreenState.h"
#include "app/SplashScreenViewInterface.h"

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

void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

void testSplashScreenStateShowsMessageOnEnter(void) {
    MockSplashScreenView mockView;
    SplashScreenState splashState(&mockView);
    
    splashState.enter();
    
    TEST_ASSERT_TRUE(mockView.showMessageWasCalled());
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(testSplashScreenStateShowsMessageOnEnter);
    
    return UNITY_END();
}
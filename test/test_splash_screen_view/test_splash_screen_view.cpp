#include "unity.h"
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

void testSplashScreenViewCanShowMessage(void) {
    MockSplashScreenView splashView;
    
    splashView.showMessage();
    
    TEST_ASSERT_TRUE(splashView.showMessageWasCalled());
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(testSplashScreenViewCanShowMessage);
    
    return UNITY_END();
}
#include <unity.h>
#include <cstring>
#include "app/SetlistMenuState.h"
#include "app/MenuControllerInterface.h"
#include "app/DiContainer.h"
#include "app/MenuLayoutViewInterface.h"
#include "mocks/MockInput.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockStateMachine.h"
#include "mocks/MockState.h"

// Mock MenuControllerInterface
class MockMenuController : public MenuControllerInterface {
private:
    char lastTitle[16];
    bool setTitleCalled = false;
    std::function<void()> selectedAction;

public:
    MenuControllerInterface* setTitle(char* title) override {
        strncpy(lastTitle, title, 16);
        lastTitle[15] = '\0';
        setTitleCalled = true;
        return this;
    }

    MenuControllerInterface* addMenuItem(char* caption, std::function<void()> action) override {
        selectedAction = action;
        return this;
    }
    MenuControllerInterface* selectNext() override { return this; }
    MenuControllerInterface* selectPrevious() override { return this; }
    void executeSelectedAction() override {
        if (selectedAction) {
            selectedAction();
        }
    }

    // Test helpers
    bool setTitleWasCalled() const { return setTitleCalled; }
    const char* getLastTitle() const { return lastTitle; }
};

void setUp(void) {
}

void tearDown(void) {
}

void testSetlistMenuStateSetsMenuTitleOnEnter() {
    // Arrange
    DiContainer container;
    MockMenuController mockMenuController;
    SetlistMenuState state(&container);
    
    container.setSetlistMenuController(&mockMenuController);
    
    char expectedTitle[] = "Setlist";
    
    // Act
    state.enter();
    
    // Assert
    TEST_ASSERT_TRUE_MESSAGE(mockMenuController.setTitleWasCalled(), 
                             "Expected setTitle to be called on enter");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expectedTitle, mockMenuController.getLastTitle(),
                                     "Expected to set correct menu title");
}

void testSetlistMenuStateBackItemTransitionsToMainApplication() {
    // Arrange
    DiContainer container;
    SetlistMenuState state(&container);

    MockMenuController mockMenuController;
    MockInput mockUserInput;
    MockStateFactory mockStateFactory;
    MockStateMachine mockStateMachine;
    MockState mockMainApplicationState;

    mockStateFactory.setMockMainApplicationState(&mockMainApplicationState);

    container.setSetlistMenuController(&mockMenuController)
        ->setUserInput(&mockUserInput)
        ->setStateFactory(&mockStateFactory)
        ->setStateMachine(&mockStateMachine);

    state.enter();

    // Act - simulate counter-clockwise rotation to select "Back" item, then press encoder button
    mockUserInput.setEncoderCounterClockwise(true);
    state.update();
    mockUserInput.setEncoderCounterClockwise(false);

    mockUserInput.setEncoderButtonPressed(true);
    state.update();
    mockUserInput.setEncoderButtonPressed(false);

    // Assert
    TEST_ASSERT_TRUE_MESSAGE(mockStateFactory.createMainApplicationStateWasCalled(),
        "Expected createMainApplicationState to be called");
    TEST_ASSERT_TRUE_MESSAGE(mockStateMachine.changeStateWasCalled(),
        "Expected changeState to be called on StateMachine");
    TEST_ASSERT_EQUAL_PTR_MESSAGE(&mockMainApplicationState, mockStateMachine.getLastChangedState(),
        "Expected state machine to transition to MainApplicationState");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(testSetlistMenuStateSetsMenuTitleOnEnter);
    RUN_TEST(testSetlistMenuStateBackItemTransitionsToMainApplication);
    return UNITY_END();
}

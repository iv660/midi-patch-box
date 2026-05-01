#include <unity.h>
#include <cstring>
#include "app/SetlistMenuState.h"
#include "app/MenuController.h"
#include "app/MenuControllerInterface.h"
#include "app/DiContainer.h"
#include "app/MenuLayoutViewInterface.h"
#include "app/SetlistMenuViewDecorator.h"
#include "mocks/MockInput.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockStateMachine.h"
#include "mocks/MockState.h"

// Mock MenuControllerInterface
class MockMenuController : public MenuControllerInterface {
private:
    char lastTitle[16];
    bool setTitleCalled = false;
    bool resetMenuItemsCalled = false;
    bool selectPreviousCalled = false;
    bool selectNextCalled = false;
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
    MenuControllerInterface* selectNext() override {
        selectNextCalled = true;
        return this;
    }
    MenuControllerInterface* selectPrevious() override {
        selectPreviousCalled = true;
        return this;
    }
    MenuControllerInterface* resetMenuItems() override {
        resetMenuItemsCalled = true;
        return this;
    }
    void executeSelectedAction() override {
        if (selectedAction) {
            selectedAction();
        }
    }

    // Test helpers
    bool setTitleWasCalled() const { return setTitleCalled; }
    bool resetMenuItemsWasCalled() const { return resetMenuItemsCalled; }
    bool selectPreviousWasCalled() const { return selectPreviousCalled; }
    bool selectNextWasCalled() const { return selectNextCalled; }
    const char* getLastTitle() const { return lastTitle; }
};

class MockMenuLayoutViewWithLastHighlightedItem : public MenuLayoutViewInterface {
private:
    char lastHighlightedCaption[16] = {0};

public:
    MenuLayoutViewInterface* displayTitle(char* title) override {
        (void)title;
        return this;
    }

    MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) override {
        (void)index;

        if (highlighted) {
            strncpy(lastHighlightedCaption, caption ? caption : (char*)"", sizeof(lastHighlightedCaption));
            lastHighlightedCaption[sizeof(lastHighlightedCaption) - 1] = '\0';
        }

        return this;
    }

    MenuLayoutViewInterface* clearItems() override {
        lastHighlightedCaption[0] = '\0';
        return this;
    }

    unsigned int getMaxItems() const override {
        return 3;
    }

    const char* getLastHighlightedItemCaption() const {
        return lastHighlightedCaption;
    }
};

class MockDiContainerForEditModeScenario : public DiContainerInterface {
private:
    MenuLayoutViewInterface* menuView = nullptr;

public:
    void setSetlistMenuLayoutView(MenuLayoutViewInterface* view) { menuView = view; }

    MenuLayoutViewInterface* getSetlistMenuLayoutView() const override { return menuView; }
    MenuControllerInterface* getSetlistMenuController() const override { return nullptr; }
    UserInputInterface* getUserInput() const override { return nullptr; }

    SplashScreenViewInterface* getSplashScreenView() const override { return nullptr; }
    IoDriverInterface* getIoDriver() const override { return nullptr; }
    StateFactoryInterface* getStateFactory() const override { return nullptr; }
    ProgramSelectorInterface* getProgramSelector() const override { return nullptr; }
    MidiControllerInterface* getMidiController() const override { return nullptr; }
    ProgramSelectionViewInterface* getProgramSelectionView() const override { return nullptr; }
    StateMachineInterface* getStateMachine() const override { return nullptr; }
    ProgramsBankInterface* getProgramsBank() const override { return nullptr; }
    ConfigMenuViewInterface* getConfigMenuView() const override { return nullptr; }
    EditSetlistViewInterface* getEditSetlistView() const override { return nullptr; }
    StateMachineInterface* getStateMachineInterface() const override { return nullptr; }
};

class MockMenuControllerWithSingleAction : public MenuControllerInterface {
private:
    std::function<void()> action;

public:
    MenuControllerInterface* setTitle(char* title) override { (void)title; return this; }
    MenuControllerInterface* addMenuItem(char* caption, std::function<void()> newAction) override {
        (void)caption;
        action = newAction;
        return this;
    }
    MenuControllerInterface* selectNext() override { return this; }
    MenuControllerInterface* selectPrevious() override { return this; }
    MenuControllerInterface* resetMenuItems() override { return this; }
    void executeSelectedAction() override {
        if (action) {
            action();
        }
    }
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
    
    char expectedTitle[] = "Edit setlist";
    
    // Act
    state.enter();
    
    // Assert
    TEST_ASSERT_TRUE_MESSAGE(mockMenuController.setTitleWasCalled(), 
                             "Expected setTitle to be called on enter");
    TEST_ASSERT_EQUAL_STRING_MESSAGE(expectedTitle, mockMenuController.getLastTitle(),
                                     "Expected to set correct menu title");
}

void testSetlistMenuStateClearsMenuItemsOnEnter() {
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

    TEST_ASSERT_TRUE_MESSAGE(mockMenuController.resetMenuItemsWasCalled(),
        "Expected resetMenuItems to be called on enter");
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

void testRotatingEncoderCounterClockwiseNavigatesUpTheList() {
	// Arrange
	DiContainer container;
	SetlistMenuState state(&container);

	MockMenuController mockMenuController;
	MockInput mockUserInput;

	container.setSetlistMenuController(&mockMenuController)
		->setUserInput(&mockUserInput);

	state.enter();

	// Act
	mockUserInput.setEncoderCounterClockwise(true);
	state.update();
	mockUserInput.setEncoderCounterClockwise(false);

	// Assert
	TEST_ASSERT_TRUE_MESSAGE(mockMenuController.selectPreviousWasCalled(),
		"Expected selectPrevious to be called when rotating encoder counter-clockwise");
}

void testRotatingEncoderClockwiseNavigatesDownTheList() {
	// Arrange
	DiContainer container;
	SetlistMenuState state(&container);

	MockMenuController mockMenuController;
	MockInput mockUserInput;

	container.setSetlistMenuController(&mockMenuController)
		->setUserInput(&mockUserInput);

	state.enter();

	// Act
	mockUserInput.setEncoderClockwise(true);
	state.update();
	mockUserInput.setEncoderClockwise(false);

	// Assert
	TEST_ASSERT_TRUE_MESSAGE(mockMenuController.selectNextWasCalled(),
		"Expected selectNext to be called when rotating encoder clockwise");
}

void testEnteringEditModeShouldShowCurrentProgramCaption() {
    int programs[] = {1, 2};
    Context context;
    context.programs = programs;
    context.programsCount = 2;

    MockInput mockUserInput;

    MockMenuLayoutViewWithLastHighlightedItem innerView;
    SetlistMenuViewDecorator viewDecorator(&innerView);

    MockDiContainerForEditModeScenario controllerContainer;
    controllerContainer.setSetlistMenuLayoutView(&viewDecorator);
    MenuController realMenuController(&controllerContainer);

    DiContainer stateContainer;
    stateContainer.setSetlistMenuController(&realMenuController)
        ->setSetlistMenuLayoutView(&viewDecorator)
        ->setUserInput(&mockUserInput);

    SetlistMenuState setlistMenuState(&stateContainer, &context);
    setlistMenuState.enter();

    char firstProgramMenuItemCaption[] = "1 ";

    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(firstProgramMenuItemCaption, innerView.getLastHighlightedItemCaption(),
        "Expecting to display current program in edit mode");
}

void testRotatingEncoderClockwiseInEditModeShouldShowNextProgramCaption() {
    int programs[] = {1, 2};
    Context context;
    context.programs = programs;
    context.programsCount = 2;

    MockInput mockUserInput;

    MockMenuLayoutViewWithLastHighlightedItem innerView;
    SetlistMenuViewDecorator viewDecorator(&innerView);

    MockDiContainerForEditModeScenario controllerContainer;
    controllerContainer.setSetlistMenuLayoutView(&viewDecorator);
    MenuController realMenuController(&controllerContainer);

    DiContainer stateContainer;
    stateContainer.setSetlistMenuController(&realMenuController)
        ->setSetlistMenuLayoutView(&viewDecorator)
        ->setUserInput(&mockUserInput);

    SetlistMenuState setlistMenuState(&stateContainer, &context);
    setlistMenuState.enter();

    char secondProgramMenuItemCaption[] = "2 ";

    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    mockUserInput.setEncoderClockwise(true);
    setlistMenuState.update();
    mockUserInput.setEncoderClockwise(false);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(secondProgramMenuItemCaption, innerView.getLastHighlightedItemCaption(),
        "Expecting to display next program when encoder gets rotated once");
}

void testRotatingEncoderClockwiseInEditShouldIterateThroughProgramsZeroToOneTwentySeven() {
    int programs[] = {5, 23, 18};
    Context context;
    context.programs = programs;
    context.programsCount = 3;

    MockInput mockUserInput;

    MockMenuLayoutViewWithLastHighlightedItem innerView;
    SetlistMenuViewDecorator viewDecorator(&innerView);

    MockDiContainerForEditModeScenario controllerContainer;
    controllerContainer.setSetlistMenuLayoutView(&viewDecorator);
    MenuController realMenuController(&controllerContainer);

    DiContainer stateContainer;
    stateContainer.setSetlistMenuController(&realMenuController)
        ->setSetlistMenuLayoutView(&viewDecorator)
        ->setUserInput(&mockUserInput);

    SetlistMenuState setlistMenuState(&stateContainer, &context);
    setlistMenuState.enter();

    char secondProgramMenuItemCaption[] = "6 ";

    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    mockUserInput.setEncoderClockwise(true);
    setlistMenuState.update();
    mockUserInput.setEncoderClockwise(false);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(secondProgramMenuItemCaption, innerView.getLastHighlightedItemCaption(),
        "Expecting to display next sequential program number when encoder gets rotated once");
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(testSetlistMenuStateSetsMenuTitleOnEnter);
    RUN_TEST(testSetlistMenuStateClearsMenuItemsOnEnter);
    RUN_TEST(testSetlistMenuStateBackItemTransitionsToMainApplication);
	RUN_TEST(testRotatingEncoderCounterClockwiseNavigatesUpTheList);
	RUN_TEST(testRotatingEncoderClockwiseNavigatesDownTheList);
    RUN_TEST(testEnteringEditModeShouldShowCurrentProgramCaption);
    RUN_TEST(testRotatingEncoderClockwiseInEditModeShouldShowNextProgramCaption);
    RUN_TEST(testRotatingEncoderClockwiseInEditShouldIterateThroughProgramsZeroToOneTwentySeven);
    return UNITY_END();
}

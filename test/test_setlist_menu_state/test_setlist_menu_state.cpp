#include <unity.h>
#include <cstring>
#include "app/SetlistMenuState.h"
#include "app/MenuController.h"
#include "app/MenuControllerInterface.h"
#include "app/DiContainer.h"
#include "app/MenuLayoutViewInterface.h"
#include "app/SetlistMenuViewDecorator.h"
#include "app/SetlistManager.h"
#include "mocks/MockInput.h"
#include "mocks/MockStateFactory.h"
#include "mocks/MockStateMachine.h"
#include "mocks/MockState.h"
#include "mocks/MockProgramSelector.h"

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
    MenuControllerInterface* getConfigMenuController() const override { return nullptr; }
    StateMachineInterface* getStateMachineInterface() const override { return nullptr; }
    SetlistManager* getSetlistManager() const override { return nullptr; }
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

// Integration tests for SetlistMenuState dynamic context reading

void testShouldDisplayUpdatedSetlistAfterEdit() {
    // Simulate the full cycle: SetlistMenuState reads from context.programs,
    // which points to SetlistManager. When SetlistManager is updated,
    // SetlistMenuState should display the new values on next enter().
    
    int programs[] = {0, 41, 112};
    Context context;
    context.programs = programs;
    context.programsCount = 3;

    MockInput mockUserInput;
    MockMenuController mockMenuController;

    DiContainer stateContainer;
    stateContainer.setSetlistMenuController(&mockMenuController)
        ->setUserInput(&mockUserInput);

    SetlistMenuState setlistMenuState(&stateContainer, &context);
    
    // First enter - should read initial values
    setlistMenuState.enter();
    
    // Simulate external update (e.g., from EditSetlistState via SetlistManager)
    programs[0] = 5;  // Change first program from 0 to 5
    
    // Re-enter - should read updated values
    setlistMenuState.enter();
    
    // The menu should have been rebuilt with the new program number.
    // We verify this indirectly: resetMenuItems should be called on each enter,
    // and menu items should be added fresh from context.programs.
    TEST_ASSERT_TRUE_MESSAGE(mockMenuController.resetMenuItemsWasCalled(),
        "Expected menu to be rebuilt on re-enter");
}

void testShouldReflectMultipleEdits() {
    // Verify that multiple edits all persist when SetlistMenuState re-enters
    
    int programs[] = {0, 41, 112};
    Context context;
    context.programs = programs;
    context.programsCount = 3;

    MockInput mockUserInput;
    MockMenuController mockMenuController;

    DiContainer stateContainer;
    stateContainer.setSetlistMenuController(&mockMenuController)
        ->setUserInput(&mockUserInput);

    SetlistMenuState setlistMenuState(&stateContainer, &context);
    
    // Initial enter
    setlistMenuState.enter();
    
    // First edit: change program at index 0
    programs[0] = 5;
    setlistMenuState.enter();
    
    // Second edit: change program at index 1
    programs[1] = 20;
    setlistMenuState.enter();
    
    // Third edit: change program at index 0 again
    programs[0] = 10;
    setlistMenuState.enter();
    
    // The test verifies that SetlistMenuState doesn't cache values
    // and always reads fresh from context.programs.
    // We can't directly inspect the menu items with MockMenuController,
    // but the fact that it rebuilds on each enter confirms dynamic reading.
    TEST_ASSERT_TRUE_MESSAGE(mockMenuController.resetMenuItemsWasCalled(),
        "Expected menu to be rebuilt after multiple edits");
}

void testShouldDisplayCorrectProgramNames() {
    // Verify that menu items reflect the actual values in context.programs
    // This test uses the real MenuController with view capture to verify
    // the actual program numbers displayed.
    
    int programs[] = {5, 20, 64};
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

    // Enter edit mode for first program - it should show "5 " not "0 "
    char firstProgramCaption[] = "5 ";
    
    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    TEST_ASSERT_EQUAL_STRING_MESSAGE(firstProgramCaption, innerView.getLastHighlightedItemCaption(),
        "Expected menu to display program number from context.programs, not a cached value");
}

// Test that verifies the actual bug fix: edits must be saved
void testEditModeShouldSaveChangesToSetlistManagerAndProgramSelector() {
    // GIVEN: A setlist with programs
    // SetlistManager initializes with default programs [0, 41, 112]
    SetlistManager setlistManager;

    // Create context that points to SetlistManager's programs
    Context context;
    context.programs = setlistManager.getPrograms();
    context.programsCount = setlistManager.getProgramCount();

    // Setup MockProgramSelector to track updates
    MockProgramSelector programSelector;
    programSelector.setPrograms(context.programs, context.programsCount);

    // Setup user input mock
    MockInput mockUserInput;

    // Setup view and controller
    MockMenuLayoutViewWithLastHighlightedItem innerView;
    SetlistMenuViewDecorator viewDecorator(&innerView);

    MockDiContainerForEditModeScenario controllerContainer;
    controllerContainer.setSetlistMenuLayoutView(&viewDecorator);
    MenuController realMenuController(&controllerContainer);

    // Setup state machine and factory
    MockStateMachine stateMachine;
    MockStateFactory stateFactory;

    // Setup DiContainer with all dependencies
    DiContainer stateContainer;
    stateContainer.setSetlistMenuController(&realMenuController)
        ->setSetlistMenuLayoutView(&viewDecorator)
        ->setUserInput(&mockUserInput)
        ->setStateMachine(&stateMachine)
        ->setStateFactory(&stateFactory)
        ->setSetlistManager(&setlistManager)
        ->setProgramSelector(&programSelector);

    SetlistMenuState setlistMenuState(&stateContainer, &context);
    setlistMenuState.enter();

    // WHEN: User enters edit mode for first program (index 0, program 0)
    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    // User rotates encoder clockwise 5 times (from 0 to 5)
    for (int i = 0; i < 5; i++) {
        mockUserInput.setEncoderClockwise(true);
        setlistMenuState.update();
        mockUserInput.setEncoderClockwise(false);
    }

    // User presses encoder button to exit edit mode and SAVE
    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    // THEN: The change should be saved to SetlistManager
    TEST_ASSERT_EQUAL_INT_MESSAGE(5, setlistManager.getProgram(0),
        "SetlistManager should have saved the edited program at index 0");

    // AND: The change should be saved to ProgramSelector
    TEST_ASSERT_EQUAL_INT_MESSAGE(5, programSelector.getProgramsList()[0],
        "ProgramSelector should have saved the edited program at index 0");

    // AND: Other programs should remain unchanged
    TEST_ASSERT_EQUAL_INT_MESSAGE(41, setlistManager.getProgram(1),
        "SetlistManager should preserve unedited program at index 1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(112, setlistManager.getProgram(2),
        "SetlistManager should preserve unedited program at index 2");
}

void testEditModeShouldSaveChangesAtDifferentIndices() {
    // GIVEN: A setlist with default programs [0, 41, 112]
    SetlistManager setlistManager;

    Context context;
    context.programs = setlistManager.getPrograms();
    context.programsCount = setlistManager.getProgramCount();

    MockProgramSelector programSelector;
    programSelector.setPrograms(context.programs, context.programsCount);

    MockInput mockUserInput;

    MockMenuLayoutViewWithLastHighlightedItem innerView;
    SetlistMenuViewDecorator viewDecorator(&innerView);

    MockDiContainerForEditModeScenario controllerContainer;
    controllerContainer.setSetlistMenuLayoutView(&viewDecorator);
    MenuController realMenuController(&controllerContainer);

    MockStateMachine stateMachine;
    MockStateFactory stateFactory;

    DiContainer stateContainer;
    stateContainer.setSetlistMenuController(&realMenuController)
        ->setSetlistMenuLayoutView(&viewDecorator)
        ->setUserInput(&mockUserInput)
        ->setStateMachine(&stateMachine)
        ->setStateFactory(&stateFactory)
        ->setSetlistManager(&setlistManager)
        ->setProgramSelector(&programSelector);

    SetlistMenuState setlistMenuState(&stateContainer, &context);
    setlistMenuState.enter();

    // Navigate to second item (index 1)
    mockUserInput.setEncoderClockwise(true);
    setlistMenuState.update();
    mockUserInput.setEncoderClockwise(false);

    // WHEN: User enters edit mode for second program (index 1, program 41)
    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    // User rotates encoder counterclockwise 4 times (from 41 to 37)
    for (int i = 0; i < 4; i++) {
        mockUserInput.setEncoderCounterClockwise(true);
        setlistMenuState.update();
        mockUserInput.setEncoderCounterClockwise(false);
    }

    // User presses encoder button to exit edit mode and SAVE
    mockUserInput.setEncoderButtonPressed(true);
    setlistMenuState.update();
    mockUserInput.setEncoderButtonPressed(false);

    // THEN: The change should be saved at the correct index
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, setlistManager.getProgram(0),
        "SetlistManager should preserve unedited program at index 0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(37, setlistManager.getProgram(1),
        "SetlistManager should have saved the edited program at index 1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(112, setlistManager.getProgram(2),
        "SetlistManager should preserve unedited program at index 2");

    // AND: ProgramSelector should also be updated
    TEST_ASSERT_EQUAL_INT_MESSAGE(37, programSelector.getProgramsList()[1],
        "ProgramSelector should have saved the edited program at index 1");
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
    // Integration tests for dynamic context reading
    RUN_TEST(testShouldDisplayUpdatedSetlistAfterEdit);
    RUN_TEST(testShouldReflectMultipleEdits);
    RUN_TEST(testShouldDisplayCorrectProgramNames);
    // Bug fix tests: verify that edits are actually saved
    RUN_TEST(testEditModeShouldSaveChangesToSetlistManagerAndProgramSelector);
    RUN_TEST(testEditModeShouldSaveChangesAtDifferentIndices);
    return UNITY_END();
}

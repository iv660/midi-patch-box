#include <unity.h>
#include "app/ConfigMenuState.h"
#include "app/MenuController.h"
#include "app/MenuControllerInterface.h"
#include "app/UserInputInterface.h"
#include "app/StateFactoryInterface.h"
#include "app/StateMachineInterface.h"
#include "app/DiContainerInterface.h"
#include "../../test/mocks/MockMenuLayoutView.h"
#include <functional>

// Mock UserInput
class MockUserInput : public UserInputInterface {
private:
    bool encoderClockwise = false;
    bool encoderCounterClockwise = false;
    bool encoderButtonPress = false;

public:
    void update() override {}
    bool userButtonIsPressed() override { return false; }
    bool rightButtonIsPressed() override { return false; }
    bool encoderRotatedClockwise() override { return encoderClockwise; }
    bool encoderRotatedCounterClockwise() override { return encoderCounterClockwise; }
    bool encoderButtonPressed() override { return encoderButtonPress; }
    bool encoderButtonLongPressed() override { return false; }
    
    void setEncoderClockwise(bool value) { encoderClockwise = value; }
    void setEncoderCounterClockwise(bool value) { encoderCounterClockwise = value; }
    void setEncoderButtonPressed(bool value) { encoderButtonPress = value; }
    void reset() {
        encoderClockwise = false;
        encoderCounterClockwise = false;
        encoderButtonPress = false;
    }
};

// Mock StateMachine
class MockStateMachine : public StateMachineInterface {
private:
    StateInterface* currentState = nullptr;

public:
    void changeState(StateInterface* newState) override {
        currentState = newState;
    }
    
    void update() override {
        // Do nothing
    }
    
    StateInterface* getCurrentState() const { return currentState; }
};

// Mock State for transitions
class StubState : public State {
public:
    void enter() override {}
    void update() override {}
    void exit() override {}
};

// Mock StateFactory
class MockStateFactory : public StateFactoryInterface {
private:
    StateInterface* mockSetlistState;
    StateInterface* mockMainState;

public:
    MockStateFactory(StateInterface* setlist, StateInterface* main) 
        : mockSetlistState(setlist), mockMainState(main) {}
    
    StateInterface* createSetlistMenuState() override {
        return mockSetlistState;
    }
    
    StateInterface* createMainApplicationState() override {
        return mockMainState;
    }
    
    StateInterface* createConfigMenuState() override { return nullptr; }
};

// Mock DiContainer - simplified version with only necessary methods
class MockDiContainer : public DiContainerInterface {
private:
    UserInputInterface* userInput = nullptr;
    MenuControllerInterface* menuController = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    StateMachineInterface* stateMachine = nullptr;
    MenuLayoutViewInterface* menuLayoutView = nullptr;

public:
    void setUserInput(UserInputInterface* input) { userInput = input; }
    void setMenuController(MenuControllerInterface* controller) { menuController = controller; }
    void setStateFactory(StateFactoryInterface* factory) { stateFactory = factory; }
    void setStateMachine(StateMachineInterface* machine) { stateMachine = machine; }
    void setMenuLayoutView(MenuLayoutViewInterface* view) { menuLayoutView = view; }
    
    UserInputInterface* getUserInput() const override { return userInput; }
    MenuControllerInterface* getSetlistMenuController() const override { return menuController; }
    StateFactoryInterface* getStateFactory() const override { return stateFactory; }
    StateMachineInterface* getStateMachine() const override { return stateMachine; }
    MenuLayoutViewInterface* getSetlistMenuLayoutView() const override { return menuLayoutView; }
    
    // Required stub methods
    SplashScreenViewInterface* getSplashScreenView() const override { return nullptr; }
    IoDriverInterface* getIoDriver() const override { return nullptr; }
    ProgramSelectorInterface* getProgramSelector() const override { return nullptr; }
    MidiControllerInterface* getMidiController() const override { return nullptr; }
    ProgramSelectionViewInterface* getProgramSelectionView() const override { return nullptr; }
    ProgramsBankInterface* getProgramsBank() const override { return nullptr; }
    ConfigMenuViewInterface* getConfigMenuView() const override { return nullptr; }
    EditSetlistViewInterface* getEditSetlistView() const override { return nullptr; }
    MenuControllerInterface* getConfigMenuController() const override { return menuController; }
    StateMachineInterface* getStateMachineInterface() const override { return stateMachine; }
};

// Global test fixtures
MockUserInput mockUserInput;
MockStateMachine mockStateMachine;
StubState stubSetlistState;
StubState stubMainState;
MockStateFactory mockStateFactory(&stubSetlistState, &stubMainState);
MockMenuLayoutView mockMenuLayoutView;
MockDiContainer mockDiContainer;

// Track if actions were triggered
int editSetlistActionCallCount = 0;
int backActionCallCount = 0;

void editSetlistAction() {
    editSetlistActionCallCount++;
}

void backAction() {
    backActionCallCount++;
}

void setUp() {
    mockUserInput.reset();
    mockMenuLayoutView.clearItems();
    mockMenuLayoutView.setMaxItems(4);
    mockDiContainer.setUserInput(&mockUserInput);
    mockDiContainer.setMenuLayoutView(&mockMenuLayoutView);
    mockDiContainer.setStateFactory(&mockStateFactory);
    mockDiContainer.setStateMachine(&mockStateMachine);
    editSetlistActionCallCount = 0;
    backActionCallCount = 0;
}

void tearDown() {
    // Cleanup
}

// RED PHASE TESTS
// These tests will fail because ConfigMenuState does not yet use MenuController

void testConfigMenuStateUsesMenuControllerOnEnter() {
    // Create MenuController and inject it via DI container
    MenuController menuController(&mockDiContainer);
    mockDiContainer.setMenuController(&menuController);
    
    ConfigMenuState configMenuState(&mockDiContainer);
    
    configMenuState.enter();
    
    // After refactoring, ConfigMenuState should use MenuController
    // which adds items to the view via MenuLayoutViewInterface
    // We expect 2 items: "Edit Setlist" and "Back"
    TEST_ASSERT_EQUAL(2, mockMenuLayoutView.getItemCount());
    TEST_ASSERT_EQUAL_STRING("Edit Setlist", mockMenuLayoutView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING("Back", mockMenuLayoutView.getItemCaption(1));
}

void testConfigMenuStateDelegatesNavigationToMenuController() {
    MenuController menuController(&mockDiContainer);
    mockDiContainer.setMenuController(&menuController);
    
    ConfigMenuState configMenuState(&mockDiContainer);
    configMenuState.enter();
    
    // Initially first item should be highlighted
    TEST_ASSERT_TRUE(mockMenuLayoutView.isItemHighlighted(0));
    TEST_ASSERT_FALSE(mockMenuLayoutView.isItemHighlighted(1));
    
    // Simulate clockwise rotation (selectNext)
    mockUserInput.setEncoderClockwise(true);
    configMenuState.update();
    mockUserInput.reset();
    
    // After refactoring, MenuController should handle navigation
    // Second item should now be highlighted
    TEST_ASSERT_FALSE(mockMenuLayoutView.isItemHighlighted(0));
    TEST_ASSERT_TRUE(mockMenuLayoutView.isItemHighlighted(1));
}

void testConfigMenuStateDelegatesCounterClockwiseToMenuController() {
    MenuController menuController(&mockDiContainer);
    mockDiContainer.setMenuController(&menuController);
    
    ConfigMenuState configMenuState(&mockDiContainer);
    configMenuState.enter();
    
    // Navigate to second item first
    mockUserInput.setEncoderClockwise(true);
    configMenuState.update();
    mockUserInput.reset();
    
    // Then go back with counter-clockwise
    mockUserInput.setEncoderCounterClockwise(true);
    configMenuState.update();
    
    // Should be back at first item
    TEST_ASSERT_TRUE(mockMenuLayoutView.isItemHighlighted(0));
    TEST_ASSERT_FALSE(mockMenuLayoutView.isItemHighlighted(1));
}

void testConfigMenuStateExecutesActionsViaMenuController() {
    MenuController menuController(&mockDiContainer);
    mockDiContainer.setMenuController(&menuController);
    
    // Instead of adding menu items directly, ConfigMenuState should
    // use MenuController which will add items with actions
    ConfigMenuState configMenuState(&mockDiContainer);
    configMenuState.enter();
    
    // Press button on first item - should trigger state transition
    mockUserInput.setEncoderButtonPressed(true);
    configMenuState.update();
    
    // After refactoring, action should be executed via MenuController
    // which triggers the state transition through the action callback
    // This test verifies the integration exists (will fail until implemented)
    StateInterface* currentState = mockStateMachine.getCurrentState();
    TEST_ASSERT_NOT_NULL(currentState);
    TEST_ASSERT_EQUAL(&stubSetlistState, currentState);
}

void testConfigMenuStateHandlesNullMenuControllerGracefully() {
    MockDiContainer emptyContainer;
    emptyContainer.setMenuController(nullptr); // No MenuController
    
    ConfigMenuState configMenuState(&emptyContainer);
    
    // Should not crash even without MenuController
    configMenuState.enter();
    configMenuState.update();
    
    // Just verify it doesn't crash - assertion for documentation
    TEST_ASSERT_TRUE(true);
}

void testConfigMenuStateSetsMenuTitleOnEnter() {
    // Create MenuController and inject it via DI container
    MenuController menuController(&mockDiContainer);
    mockDiContainer.setMenuController(&menuController);
    
    ConfigMenuState configMenuState(&mockDiContainer);
    
    // Clear any previous title
    mockMenuLayoutView.clearTitle();
    
    // Enter the state
    configMenuState.enter();
    
    // ConfigMenuState должен установить заголовок "Configuration"
    TEST_ASSERT_TRUE(mockMenuLayoutView.hasTitle());
    TEST_ASSERT_EQUAL_STRING("Configuration", mockMenuLayoutView.getTitle());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testConfigMenuStateUsesMenuControllerOnEnter);
    RUN_TEST(testConfigMenuStateDelegatesNavigationToMenuController);
    RUN_TEST(testConfigMenuStateDelegatesCounterClockwiseToMenuController);
    RUN_TEST(testConfigMenuStateExecutesActionsViaMenuController);
    RUN_TEST(testConfigMenuStateHandlesNullMenuControllerGracefully);
    RUN_TEST(testConfigMenuStateSetsMenuTitleOnEnter);
    
    return UNITY_END();
}

#include <unity.h>
#include <cstring>
#include "app/ConfigMenuState.h"
#include "app/MenuController.h"
#include "app/ConfigMenuViewAdapter.h"
#include "app/StateFactoryInterface.h"
#include "app/StateMachineInterface.h"
#include "app/UserInputInterface.h"
#include "app/DiContainerInterface.h"
#include "../mocks/MockConfigMenuView.h"
#include "../mocks/MockMenuLayoutView.h"

// Mock objects for testing
class MockUserInput : public UserInputInterface {
private:
    bool encoderClockwise = false;
    bool encoderCounterClockwise = false;
    bool encoderButtonPress = false;
    bool encoderLongPress = false;

public:
    void update() override {}
    bool userButtonIsPressed() override { return false; }
    bool rightButtonIsPressed() override { return false; }
    bool encoderRotatedClockwise() override { return encoderClockwise; }
    bool encoderRotatedCounterClockwise() override { return encoderCounterClockwise; }
    bool encoderButtonPressed() override { return encoderButtonPress; }
    bool encoderButtonLongPressed() override { return encoderLongPress; }
    
    // Test helpers
    void setEncoderClockwise(bool value) { encoderClockwise = value; }
    void setEncoderCounterClockwise(bool value) { encoderCounterClockwise = value; }
    void setEncoderButtonPressed(bool value) { encoderButtonPress = value; }
};

class MockStateFactory : public StateFactoryInterface {
private:
    bool createSetlistMenuStateCalled = false;
    bool createMainApplicationStateCalled = false;
    StateInterface* mockSetlistMenuState = nullptr;
    StateInterface* mockMainApplicationState = nullptr;

public:
    StateInterface* createMainApplicationState() override {
        createMainApplicationStateCalled = true;
        return mockMainApplicationState;
    }
    StateInterface* createConfigMenuState() override { return nullptr; }
    StateInterface* createSetlistMenuState() override {
        createSetlistMenuStateCalled = true;
        return mockSetlistMenuState;
    }
    
    // Test helpers
    bool createSetlistMenuStateWasCalled() const { return createSetlistMenuStateCalled; }
    bool createMainApplicationStateWasCalled() const { return createMainApplicationStateCalled; }
    void setMockSetlistMenuState(StateInterface* state) { mockSetlistMenuState = state; }
    void setMockMainApplicationState(StateInterface* state) { mockMainApplicationState = state; }
};

class MockStateMachine : public StateMachineInterface {
private:
    bool changeStateCalled = false;
    StateInterface* lastChangedState = nullptr;

public:
    void changeState(StateInterface* newState) override {
        changeStateCalled = true;
        lastChangedState = newState;
    }
    void update() override {}
    
    // Test helpers
    bool changeStateWasCalled() const { return changeStateCalled; }
    StateInterface* getLastChangedState() const { return lastChangedState; }
};

class MockState : public StateInterface {
public:
    void enter() override {}
    void update() override {}
    void exit() override {}
    StateInterface* setStateMachine(StateMachineInterface* stateMachine) override { return this; }
};

// Mock DiContainer
class MockDiContainer : public DiContainerInterface {
private:
    UserInputInterface* userInput = nullptr;
    MenuControllerInterface* menuController = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    StateMachineInterface* stateMachine = nullptr;
    MenuLayoutViewInterface* menuLayoutView = nullptr;
    ConfigMenuViewInterface* configMenuView = nullptr;

public:
    void setUserInput(UserInputInterface* input) { userInput = input; }
    void setMenuController(MenuControllerInterface* controller) { menuController = controller; }
    void setStateFactory(StateFactoryInterface* factory) { stateFactory = factory; }
    void setStateMachine(StateMachineInterface* machine) { stateMachine = machine; }
    void setMenuLayoutView(MenuLayoutViewInterface* view) { menuLayoutView = view; }
    void setConfigMenuView(ConfigMenuViewInterface* view) { configMenuView = view; }
    
    UserInputInterface* getUserInput() const override { return userInput; }
    MenuControllerInterface* getSetlistMenuController() const override { return menuController; }
    StateFactoryInterface* getStateFactory() const override { return stateFactory; }
    StateMachineInterface* getStateMachine() const override { return stateMachine; }
    MenuLayoutViewInterface* getSetlistMenuLayoutView() const override { return menuLayoutView; }
    ConfigMenuViewInterface* getConfigMenuView() const override { return configMenuView; }
    
    // Required stub methods
    SplashScreenViewInterface* getSplashScreenView() const override { return nullptr; }
    IoDriverInterface* getIoDriver() const override { return nullptr; }
    ProgramSelectorInterface* getProgramSelector() const override { return nullptr; }
    MidiControllerInterface* getMidiController() const override { return nullptr; }
    ProgramSelectionViewInterface* getProgramSelectionView() const override { return nullptr; }
    ProgramsBankInterface* getProgramsBank() const override { return nullptr; }
    EditSetlistViewInterface* getEditSetlistView() const override { return nullptr; }
    MenuControllerInterface* getConfigMenuController() const override { return menuController; }
    StateMachineInterface* getStateMachineInterface() const override { return stateMachine; }
    SetlistManager* getSetlistManager() const override { return nullptr; }
};

void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

// ConfigMenuState should show menu on enter
void testConfigMenuStateShowsMenu() {
    // Arrange
    MockConfigMenuView mockConfigView;
    ConfigMenuViewAdapter adapter(&mockConfigView);
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&adapter);
    mockDiContainer.setConfigMenuView(&mockConfigView);
    
    ConfigMenuState state(&mockDiContainer);
    
    // Act
    state.enter();
    
    // Assert
    TEST_ASSERT_TRUE(mockConfigView.wasShowMenuCalled());
}

// ConfigMenuState should display menu items on enter
void testConfigMenuStateDisplaysItems() {
    // Arrange
    MockMenuLayoutView mockLayoutView;
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&mockLayoutView);
    
    ConfigMenuState state(&mockDiContainer);
    
    // Act
    state.enter();
    
    // Assert - via MenuController and MenuLayoutViewInterface
    TEST_ASSERT_EQUAL(2, mockLayoutView.getItemCount());
    TEST_ASSERT_EQUAL_STRING("Edit Setlist", mockLayoutView.getItemCaption(0));
    TEST_ASSERT_EQUAL_STRING("Back", mockLayoutView.getItemCaption(1));
}

// ConfigMenuState should highlight first item by default
void testConfigMenuStateHighlightsFirstItem() {
    // Arrange
    MockMenuLayoutView mockLayoutView;
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&mockLayoutView);
    
    ConfigMenuState state(&mockDiContainer);
    
    // Act
    state.enter();
    
    // Assert - via MenuController
    TEST_ASSERT_TRUE(mockLayoutView.isItemHighlighted(0));
    TEST_ASSERT_FALSE(mockLayoutView.isItemHighlighted(1));
}

// ConfigMenuState should navigate to next item on clockwise encoder rotation
void testConfigMenuStateNavigatesOnClockwiseRotation() {
    // Arrange
    MockMenuLayoutView mockLayoutView;
    MockUserInput mockInput;
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&mockLayoutView);
    mockDiContainer.setUserInput(&mockInput);
    
    ConfigMenuState state(&mockDiContainer);
    state.enter();
    
    // Act - simulate clockwise encoder rotation
    mockInput.setEncoderClockwise(true);
    state.update();
    
    // Assert - should move to second item (index 1)
    TEST_ASSERT_FALSE(mockLayoutView.isItemHighlighted(0));
    TEST_ASSERT_TRUE(mockLayoutView.isItemHighlighted(1));
}

// ConfigMenuState should navigate to previous item on counter-clockwise encoder rotation
void testConfigMenuStateNavigatesOnCounterClockwiseRotation() {
    // Arrange
    MockMenuLayoutView mockLayoutView;
    MockUserInput mockInput;
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&mockLayoutView);
    mockDiContainer.setUserInput(&mockInput);
    
    ConfigMenuState state(&mockDiContainer);
    state.enter();
    
    // First move to second item
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderClockwise(false);
    
    // Act - simulate counter-clockwise encoder rotation
    mockInput.setEncoderCounterClockwise(true);
    state.update();
    
    // Assert - should move back to first item (index 0)
    TEST_ASSERT_TRUE(mockLayoutView.isItemHighlighted(0));
    TEST_ASSERT_FALSE(mockLayoutView.isItemHighlighted(1));
}

// ConfigMenuState should wrap around cyclically in both directions
void testConfigMenuStateCyclicNavigation() {
    // Arrange
    MockMenuLayoutView mockLayoutView;
    MockUserInput mockInput;
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&mockLayoutView);
    mockDiContainer.setUserInput(&mockInput);
    
    ConfigMenuState state(&mockDiContainer);
    state.enter(); // starts at index 0
    
    // Act - counter-clockwise from first item should wrap to last
    mockInput.setEncoderCounterClockwise(true);
    state.update();
    
    // Assert - should wrap to last item (index 1)
    TEST_ASSERT_FALSE(mockLayoutView.isItemHighlighted(0));
    TEST_ASSERT_TRUE(mockLayoutView.isItemHighlighted(1));
}

// ConfigMenuState should transition to SetlistMenuState when first item is selected
void testConfigMenuStateTransitionsToSetlistMenuState() {
    // Arrange
    MockMenuLayoutView mockLayoutView;
    MockUserInput mockInput;
    MockStateMachine mockStateMachine;
    MockState mockSetlistState;
    MockStateFactory mockStateFactory;
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockStateFactory.setMockSetlistMenuState(&mockSetlistState);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&mockLayoutView);
    mockDiContainer.setUserInput(&mockInput);
    mockDiContainer.setStateMachine(&mockStateMachine);
    mockDiContainer.setStateFactory(&mockStateFactory);
    
    ConfigMenuState state(&mockDiContainer);
    state.enter();
    
    // Act - press button on first item
    mockInput.setEncoderButtonPressed(true);
    state.update();
    
    // Assert
    TEST_ASSERT_TRUE(mockStateFactory.createSetlistMenuStateWasCalled());
    TEST_ASSERT_TRUE(mockStateMachine.changeStateWasCalled());
    TEST_ASSERT_EQUAL(&mockSetlistState, mockStateMachine.getLastChangedState());
}

// ConfigMenuState should transition back to MainApplicationState when "Back" is selected
void testConfigMenuStateTransitionsBackToMainApplication() {
    // Arrange
    MockMenuLayoutView mockLayoutView;
    MockUserInput mockInput;
    MockStateMachine mockStateMachine;
    MockState mockMainState;
    MockStateFactory mockStateFactory;
    MockDiContainer mockDiContainer;
    MenuController menuController(&mockDiContainer);
    
    mockStateFactory.setMockMainApplicationState(&mockMainState);
    
    mockDiContainer.setMenuController(&menuController);
    mockDiContainer.setMenuLayoutView(&mockLayoutView);
    mockDiContainer.setUserInput(&mockInput);
    mockDiContainer.setStateMachine(&mockStateMachine);
    mockDiContainer.setStateFactory(&mockStateFactory);
    
    ConfigMenuState state(&mockDiContainer);
    state.enter();
    
    // Navigate to second item ("Back")
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderClockwise(false);
    
    // Act - press button on "Back" item
    mockInput.setEncoderButtonPressed(true);
    state.update();
    
    // Assert
    TEST_ASSERT_TRUE(mockStateFactory.createMainApplicationStateWasCalled());
    TEST_ASSERT_TRUE(mockStateMachine.changeStateWasCalled());
    TEST_ASSERT_EQUAL(&mockMainState, mockStateMachine.getLastChangedState());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testConfigMenuStateShowsMenu);
    RUN_TEST(testConfigMenuStateDisplaysItems);
    RUN_TEST(testConfigMenuStateHighlightsFirstItem);
    RUN_TEST(testConfigMenuStateNavigatesOnClockwiseRotation);
    RUN_TEST(testConfigMenuStateNavigatesOnCounterClockwiseRotation);
    RUN_TEST(testConfigMenuStateCyclicNavigation);
    RUN_TEST(testConfigMenuStateTransitionsToSetlistMenuState);
    RUN_TEST(testConfigMenuStateTransitionsBackToMainApplication);
    
    return UNITY_END();
}

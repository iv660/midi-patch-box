#include <unity.h>
#include <cstring>
#include "app/ConfigMenuState.h"
#include "app/ConfigMenuViewInterface.h"
#include "app/StateFactoryInterface.h"
#include "app/StateMachineInterface.h"
#include "app/UserInputInterface.h"
#include "app/StateFactoryInterface.h"
#include "app/StateMachineInterface.h"
#include "app/DiContainer.h"

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

class MockConfigMenuView : public ConfigMenuViewInterface {
private:
    bool showMenuCalled = false;
    bool setSelectedItemCalled = false;
    int selectedItem = -1;
    int displayMenuItemCallCount = 0;
    int displayedItemIndices[10]; // Store up to 10 calls
    const char* displayedItemNames[10];

public:
    ConfigMenuViewInterface* showMenu() override {
        showMenuCalled = true;
        return this;
    }
    
    ConfigMenuViewInterface* setSelectedItem(int itemIndex) override {
        selectedItem = itemIndex;
        setSelectedItemCalled = true;
        return this;
    }
    
    ConfigMenuViewInterface* displayMenuItem(int itemIndex, const char* itemName) override {
        if (displayMenuItemCallCount < 10) {
            displayedItemIndices[displayMenuItemCallCount] = itemIndex;
            displayedItemNames[displayMenuItemCallCount] = itemName;
            displayMenuItemCallCount++;
        }
        return this;
    }
    
    // Test helpers
    bool showMenuWasCalled() const { return showMenuCalled; }
    bool setSelectedItemWasCalled() const { return setSelectedItemCalled; }
    int getSelectedItem() const { return selectedItem; }
    int getDisplayMenuItemCallCount() const { return displayMenuItemCallCount; }
    const char* getDisplayedItemName(int callIndex) const {
        return (callIndex < displayMenuItemCallCount) ? displayedItemNames[callIndex] : nullptr;
    }
    int getDisplayedItemIndex(int callIndex) const {
        return (callIndex < displayMenuItemCallCount) ? displayedItemIndices[callIndex] : -1;
    }
    const char* getLastDisplayedItemName() const {
        return (displayMenuItemCallCount > 0) ? displayedItemNames[displayMenuItemCallCount - 1] : nullptr;
    }
    
    bool itemWasDisplayed(const char* itemName) const {
        for (int i = 0; i < displayMenuItemCallCount; i++) {
            if (displayedItemNames[i] && strcmp(displayedItemNames[i], itemName) == 0) {
                return true;
            }
        }
        return false;
    }
};

class MockStateFactory : public StateFactoryInterface {
private:
    bool createEditSetlistStateCalled = false;
    bool createMainApplicationStateCalled = false;
    StateInterface* mockEditSetlistState = nullptr;
    StateInterface* mockMainApplicationState = nullptr;

public:
    StateInterface* createMainApplicationState() override {
        createMainApplicationStateCalled = true;
        return mockMainApplicationState;
    }
    StateInterface* createConfigMenuState() override { return nullptr; }
    StateInterface* createEditSetlistState() override {
        createEditSetlistStateCalled = true;
        return mockEditSetlistState;
    }
    
    // Test helpers
    bool createEditSetlistStateWasCalled() const { return createEditSetlistStateCalled; }
    bool createMainApplicationStateWasCalled() const { return createMainApplicationStateCalled; }
    void setMockEditSetlistState(StateInterface* state) { mockEditSetlistState = state; }
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

void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

// ConfigMenuState should show menu on enter
void testConfigMenuStateShowsMenu() {
    // Arrange
    ConfigMenuState state;
    MockConfigMenuView mockView;
    
    state.setConfigMenuView(&mockView);
    
    // Act
    state.enter();
    
    // Assert
    TEST_ASSERT_TRUE(mockView.showMenuWasCalled());
}

// ConfigMenuState should display menu items on enter
void testConfigMenuStateDisplaysItems() {
    // Arrange
    ConfigMenuState state;
    MockConfigMenuView mockView;
    
    state.setConfigMenuView(&mockView);
    
    // Act
    state.enter();
    
    // Assert
    TEST_ASSERT_TRUE(mockView.itemWasDisplayed("Edit Setlist"));
    TEST_ASSERT_TRUE(mockView.itemWasDisplayed("Back"));
}

// ConfigMenuState should highlight first item by default
void testConfigMenuStateHighlightsFirstItem() {
    // Arrange
    ConfigMenuState state;
    MockConfigMenuView mockView;
    
    state.setConfigMenuView(&mockView);
    
    // Act
    state.enter();
    
    // Assert
    TEST_ASSERT_EQUAL(0, mockView.getSelectedItem());
}

// ConfigMenuState should navigate to next item on clockwise encoder rotation
void testConfigMenuStateNavigatesOnClockwiseRotation() {
    // Arrange
    ConfigMenuState state;
    MockConfigMenuView mockView;
    MockUserInput mockInput;
    
    state.setConfigMenuView(&mockView);
    state.setUserInput(&mockInput);
    state.enter();
    
    // Act - simulate clockwise encoder rotation
    mockInput.setEncoderClockwise(true);
    state.update();
    
    // Assert - should move to second item (index 1)
    TEST_ASSERT_EQUAL(1, mockView.getSelectedItem());
}

// ConfigMenuState should navigate to previous item on counter-clockwise encoder rotation
void testConfigMenuStateNavigatesOnCounterClockwiseRotation() {
    // Arrange
    ConfigMenuState state;
    MockConfigMenuView mockView;
    MockUserInput mockInput;
    
    state.setConfigMenuView(&mockView);
    state.setUserInput(&mockInput);
    state.enter();
    
    // First move to second item
    mockInput.setEncoderClockwise(true);
    state.update();
    mockInput.setEncoderClockwise(false);
    
    // Act - simulate counter-clockwise encoder rotation
    mockInput.setEncoderCounterClockwise(true);
    state.update();
    
    // Assert - should move back to first item (index 0)
    TEST_ASSERT_EQUAL(0, mockView.getSelectedItem());
}

// ConfigMenuState should wrap around cyclically in both directions
void testConfigMenuStateCyclicNavigation() {
    // Arrange
    ConfigMenuState state;
    MockConfigMenuView mockView;
    MockUserInput mockInput;
    
    state.setConfigMenuView(&mockView);
    state.setUserInput(&mockInput);
    state.enter(); // starts at index 0
    
    // Act & Assert - clockwise from last item should wrap to first
    mockInput.setEncoderClockwise(true);
    state.update(); // now at index 1
    state.update(); // should wrap to index 0
    TEST_ASSERT_EQUAL(0, mockView.getSelectedItem());
    
    // Reset encoder state
    mockInput.setEncoderClockwise(false);
    
    // Act & Assert - counter-clockwise from first item should wrap to last
    mockInput.setEncoderCounterClockwise(true);
    state.update(); // should wrap to index 1
    TEST_ASSERT_EQUAL(1, mockView.getSelectedItem());
}

// ConfigMenuState should transition to EditSetlistState when encoder button pressed on Edit Setlist
void testConfigMenuStateTransitionsToEditSetlist() {
    // Arrange
    ConfigMenuState state;
    MockConfigMenuView mockView;
    MockUserInput mockInput;
    MockStateFactory mockFactory;
    MockStateMachine mockStateMachine;
    MockState mockEditSetlistState;
    
    mockFactory.setMockEditSetlistState(&mockEditSetlistState);
    
    state.setConfigMenuView(&mockView);
    state.setUserInput(&mockInput);
    state.setStateFactory(&mockFactory);
    state.setStateMachine(&mockStateMachine);
    state.enter(); // starts at index 0 (Edit Setlist)
    
    // Act - simulate encoder button press
    mockInput.setEncoderButtonPressed(true);
    state.update();
    
    // Assert - should create EditSetlistState and change to it
    TEST_ASSERT_TRUE(mockFactory.createEditSetlistStateWasCalled());
    TEST_ASSERT_TRUE(mockStateMachine.changeStateWasCalled());
    TEST_ASSERT_EQUAL_PTR(&mockEditSetlistState, mockStateMachine.getLastChangedState());
}

// ConfigMenuState should transition to EditSetlistState when encoder button pressed on Edit Setlist
void testConfigMenuStateTransitionsBackToMainApplication() {
    // Arrange
    DiContainer container;
    ConfigMenuState state(&container);

    MockConfigMenuView mockView;
    MockUserInput mockInput;
    MockStateFactory mockFactory;
    MockStateMachine mockStateMachine;
    MockState mockMainApplicationState;

    container.setStateMachine(&mockStateMachine)
        ->setStateFactory(&mockFactory)
        ->setUserInput(&mockInput)
        ->setConfigMenuView(&mockView);
    
    mockFactory.setMockMainApplicationState(&mockMainApplicationState);

    state.enter(); // starts at index 0 (Edit Setlist)
    
    // Act - simulate encoder button press
    mockInput.setEncoderClockwise(true);
    state.update(); // now at index 1
    mockInput.setEncoderClockwise(false);

    mockInput.setEncoderButtonPressed(true);
    state.update();
    mockInput.setEncoderButtonPressed(false);
    
    
    // Assert - should create EditSetlistState and change to it
    TEST_ASSERT_TRUE(mockFactory.createMainApplicationStateWasCalled());
    TEST_ASSERT_TRUE(mockStateMachine.changeStateWasCalled());
    TEST_ASSERT_EQUAL_PTR(&mockMainApplicationState, mockStateMachine.getLastChangedState());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testConfigMenuStateShowsMenu);
    RUN_TEST(testConfigMenuStateDisplaysItems);
    RUN_TEST(testConfigMenuStateHighlightsFirstItem);
    RUN_TEST(testConfigMenuStateNavigatesOnClockwiseRotation);
    RUN_TEST(testConfigMenuStateNavigatesOnCounterClockwiseRotation);
    RUN_TEST(testConfigMenuStateCyclicNavigation);
    RUN_TEST(testConfigMenuStateTransitionsToEditSetlist);
    RUN_TEST(testConfigMenuStateTransitionsBackToMainApplication);
    
    return UNITY_END();
}
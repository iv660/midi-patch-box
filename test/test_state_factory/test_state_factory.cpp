#include <unity.h>
#include "app/StateFactory.h"
#include "app/StateFactoryInterface.h"
#include "app/MainApplicationState.h"
#include "app/ConfigMenuViewInterface.h"
#include "app/EditSetlistViewInterface.h"
#include "app/DiContainerInterface.h"
#include "mocks/MockIoDriver.h"
#include "mocks/MockButton.h"
#include "mocks/MockEncoder.h"

// Mock objects for testing
class MockUserInput : public UserInputInterface {
public:
    void update() override {}
    bool userButtonIsPressed() override { return false; }
    bool rightButtonIsPressed() override { return false; }
    bool encoderRotatedClockwise() override { return false; }
    bool encoderRotatedCounterClockwise() override { return false; }
    bool encoderButtonPressed() override { return false; }
    bool encoderButtonLongPressed() override { return false; }
};

class MockProgramSelector : public ProgramSelectorInterface {
public:
    void selectNextProgram() override {}
    void selectPreviousProgram() override {}
    int getSelectedProgramNumber() const override { return 0; }
    ProgramSelectorInterface* setPrograms(std::initializer_list<int> programs) override { return this; }
    void updateProgram(int index, int programNumber) override {}
};

class MockMidiController : public MidiControllerInterface {
public:
    void sendProgramChange(int program) override {}
    void begin() override {}
};

class MockProgramSelectionView : public ProgramSelectionViewInterface {
public:
    ProgramSelectionViewInterface* setSelectedProgramNumber(int programNumber) override { return this; }
    ProgramSelectionViewInterface* displayProgramName(const char* programName) override { return this; }
    ProgramSelectionViewInterface* highlightProgram() override { return this; }
    ProgramSelectionViewInterface* clearHighlight() override { return this; }
};

class MockProgramsBank : public ProgramsBankInterface {
public:
    ProgramsBankInterface* addProgram(int programNumber, const char* programName) override { return this; }
    const char* getProgramName(int programNumber) override { return "Test"; }
    const Program* getAllPrograms(int& count) const override {
        static Program programs[1] = {{1, "Test"}};
        count = 1;
        return programs;
    }
};

class MockConfigMenuView : public ConfigMenuViewInterface {
public:
    ConfigMenuViewInterface* showMenu() override { return this; }
    ConfigMenuViewInterface* setSelectedItem(int itemIndex) override { return this; }
    ConfigMenuViewInterface* displayMenuItem(int itemIndex, const char* itemName) override { return this; }
};

class MockEditSetlistView : public EditSetlistViewInterface {
public:
    void showSetlist(Program* setlist) override {}
    void setSelectedItemIndex(int index) override {}
    void setEditMode(bool enabled) override {}
    void setEditedProgramIndex(int index) override {}
    void setEditedProgramNumber(int programNumber) override {}
    void setEditedProgramName(const char* programName) override {}
};

class MockStateMachine : public StateMachineInterface {
public:
    void changeState(StateInterface* newState) override {}
    void update() override {}
};

class MockDiContainer : public DiContainerInterface {
private:
    mutable MockUserInput mockUserInput;
    mutable MockProgramSelector mockProgramSelector;
    mutable MockMidiController mockMidiController;
    mutable MockProgramSelectionView mockProgramSelectionView;
    mutable MockProgramsBank mockProgramsBank;
    mutable MockConfigMenuView mockConfigMenuView;
    mutable MockEditSetlistView mockEditSetlistView;
    mutable MockStateMachine mockStateMachine;

public:
    // Call counters
    mutable int getUserInputCallCount = 0;
    mutable int getProgramSelectorCallCount = 0;
    mutable int getMidiControllerCallCount = 0;
    mutable int getProgramSelectionViewCallCount = 0;
    mutable int getStateMachineCallCount = 0;
    mutable int getProgramsBankCallCount = 0;
    mutable int getConfigMenuViewCallCount = 0;
    mutable int getStateMachineInterfaceCallCount = 0;

    // SplashScreenState dependencies
    SplashScreenViewInterface* getSplashScreenView() const override { return nullptr; }
    IoDriverInterface* getIoDriver() const override { return nullptr; }
    StateFactoryInterface* getStateFactory() const override { return nullptr; }
    
    // MidiPatchBoxApplication dependencies
    UserInputInterface* getUserInput() const override {
        getUserInputCallCount++;
        return &mockUserInput;
    }
    ProgramSelectorInterface* getProgramSelector() const override {
        getProgramSelectorCallCount++;
        return &mockProgramSelector;
    }
    MidiControllerInterface* getMidiController() const override {
        getMidiControllerCallCount++;
        return &mockMidiController;
    }
    ProgramSelectionViewInterface* getProgramSelectionView() const override {
        getProgramSelectionViewCallCount++;
        return &mockProgramSelectionView;
    }
    StateMachineInterface* getStateMachine() const override {
        getStateMachineCallCount++;
        return &mockStateMachine;
    }
    
    // StateFactory dependencies
    ProgramsBankInterface* getProgramsBank() const override {
        getProgramsBankCallCount++;
        return &mockProgramsBank;
    }
    ConfigMenuViewInterface* getConfigMenuView() const override {
        getConfigMenuViewCallCount++;
        return &mockConfigMenuView;
    }
    EditSetlistViewInterface* getEditSetlistView() const override {
        return &mockEditSetlistView;
    }
    StateMachineInterface* getStateMachineInterface() const override {
        getStateMachineInterfaceCallCount++;
        return &mockStateMachine;
    }
};

void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

void testStateFactoryCreatesMainApplicationState() {
    // Arrange
    MockDiContainer mockContainer;
    StateFactory factory(&mockContainer);
    
    // Act
    StateInterface* state = factory.createMainApplicationState();
    
    // Assert
    TEST_ASSERT_NOT_NULL(state);
    
    // Verify it's actually a MainApplicationState
    MainApplicationState* mainState = dynamic_cast<MainApplicationState*>(state);
    TEST_ASSERT_NOT_NULL(mainState);
    
    // Clean up
    delete state;
}

void testStateFactoryCanCreateConfigMenuState() {
    // Arrange
    MockDiContainer mockContainer;
    StateFactory factory(&mockContainer);
    
    // Act
    StateInterface* state = factory.createConfigMenuState();
    
    // Assert
    TEST_ASSERT_NOT_NULL(state);
    
    // Clean up
    delete state;
}

void testStateFactoryWithDiContainerCreatesMainApplicationState() {
    // Arrange
    MockDiContainer mockContainer;
    StateFactory factory(&mockContainer);
    
    // Don't set any dependencies directly - should get them from DI container
    
    // Act
    StateInterface* state = factory.createMainApplicationState();
    
    // Assert
    TEST_ASSERT_NOT_NULL(state);
    
    // Verify it's actually a MainApplicationState
    MainApplicationState* mainState = dynamic_cast<MainApplicationState*>(state);
    TEST_ASSERT_NOT_NULL(mainState);
    
    // Verify that dependencies were requested from DI container
    TEST_ASSERT_GREATER_THAN(0, mockContainer.getUserInputCallCount);
    TEST_ASSERT_GREATER_THAN(0, mockContainer.getProgramSelectorCallCount);
    TEST_ASSERT_GREATER_THAN(0, mockContainer.getMidiControllerCallCount);
    TEST_ASSERT_GREATER_THAN(0, mockContainer.getProgramSelectionViewCallCount);
    TEST_ASSERT_GREATER_THAN(0, mockContainer.getProgramsBankCallCount);
    TEST_ASSERT_GREATER_THAN(0, mockContainer.getStateMachineInterfaceCallCount);
    
    // Clean up
    delete state;
}

void testStateFactoryWithDiContainerCreatesConfigMenuState() {
    // Arrange
    MockDiContainer mockContainer;
    StateFactory factory(&mockContainer);
    
    // Don't set any dependencies directly - should get them from DI container
    
    // Act
    StateInterface* state = factory.createConfigMenuState();
    
    // Assert
    TEST_ASSERT_NOT_NULL(state);
    
    // Clean up
    delete state;
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(testStateFactoryCreatesMainApplicationState);
    RUN_TEST(testStateFactoryCanCreateConfigMenuState);
    RUN_TEST(testStateFactoryWithDiContainerCreatesMainApplicationState);
    RUN_TEST(testStateFactoryWithDiContainerCreatesConfigMenuState);
    
    return UNITY_END();
}
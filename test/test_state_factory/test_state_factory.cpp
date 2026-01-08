#include <unity.h>
#include "app/StateFactory.h"
#include "app/StateFactoryInterface.h"
#include "app/MainApplicationState.h"
#include "app/ConfigMenuViewInterface.h"
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
};

class MockConfigMenuView : public ConfigMenuViewInterface {
public:
    ConfigMenuViewInterface* showMenu() override { return this; }
    ConfigMenuViewInterface* setSelectedItem(int itemIndex) override { return this; }
    ConfigMenuViewInterface* displayMenuItem(int itemIndex, const char* itemName) override { return this; }
};

void setUp(void) {
    // Set up code here, to run before each test
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

void test_state_factory_creates_main_application_state() {
    // Arrange
    StateFactory factory;
    MockUserInput mockUserInput;
    MockProgramSelector mockProgramSelector;
    MockMidiController mockMidiController;
    MockProgramSelectionView mockProgramSelectionView;
    MockProgramsBank mockProgramsBank;
    
    factory.setUserInput(&mockUserInput)
        ->setProgramSelector(&mockProgramSelector)
        ->setMidiController(&mockMidiController)
        ->setProgramSelectionView(&mockProgramSelectionView)
        ->setProgramsBank(&mockProgramsBank);
    
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

void test_state_factory_fluent_interface() {
    // Arrange
    StateFactory factory;
    MockUserInput mockUserInput;
    MockProgramSelector mockProgramSelector;
    MockMidiController mockMidiController;
    MockProgramSelectionView mockProgramSelectionView;
    MockProgramsBank mockProgramsBank;
    
    // Act - test fluent interface
    StateFactory* result = factory.setUserInput(&mockUserInput)
        ->setProgramSelector(&mockProgramSelector)
        ->setMidiController(&mockMidiController)
        ->setProgramSelectionView(&mockProgramSelectionView)
        ->setProgramsBank(&mockProgramsBank);
    
    // Assert
    TEST_ASSERT_EQUAL_PTR(&factory, result);
}

void test_state_factory_can_create_config_menu_state() {
    // Arrange
    StateFactory factory;
    MockUserInput mockUserInput;
    MockConfigMenuView mockConfigMenuView;
    
    factory.setUserInput(&mockUserInput)
        ->setConfigMenuView(&mockConfigMenuView);
    
    // Act
    StateInterface* state = factory.createConfigMenuState();
    
    // Assert
    TEST_ASSERT_NOT_NULL(state);
    
    // Clean up
    delete state;
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_state_factory_creates_main_application_state);
    RUN_TEST(test_state_factory_fluent_interface);
    RUN_TEST(test_state_factory_can_create_config_menu_state);
    
    return UNITY_END();
}
#include "unity.h"
#include "app/MidiPatchBoxApplication.h"
#include "app/UserInputInterface.h"
#include "app/ProgramSelectorInterface.h"

class MockUserInput : public UserInputInterface {
public:
    bool userButtonIsPressed() override {
        return true; // Simulate button press
    }
};

class MockProgramSelector : public ProgramSelectorInterface {
private:
    int16_t selectedProgram = 2;
public:
    void selectNextProgram() override {
        selectedProgram++;
    }

    int16_t getSelectedProgram() const {
        return selectedProgram;
    }
};

class MockMidiController : public MidiControllerInterface {
public:
    void sendProgramChange(int program) override {
        // Simulate sending a program change
    }
};

void setUp(void) {
    // Called before each test
}

void tearDown(void) {
    // Called after each test
}

// Test that tick() method can be called without error
void testShouldSupportTickMethod(void) {
    MidiPatchBoxApplication app;

    app.tick();
}

void testShouldSelectNextProgramOnUserButtonPress(void) {
    MidiPatchBoxApplication app;
    
    MockUserInput userInput;
    MockProgramSelector programSelector;

    app.setUserInput(&userInput)
       ->setProgramSelector(&programSelector);
    
    app.tick();

    TEST_ASSERT_EQUAL_INT16(3, programSelector.getSelectedProgram());
}

void testShouldSendProgramChangeOnUserButtonPress(void) {
    // MidiPatchBoxApplication app;

    // MockUserInput userInput;
    
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(testShouldSupportTickMethod);
    RUN_TEST(testShouldSelectNextProgramOnUserButtonPress);
    return UNITY_END();
}

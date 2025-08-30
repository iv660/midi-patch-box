#include "unity.h"
#include "app/MidiPatchBoxApplication.h"
#include "app/UserInputInterface.h"
#include "app/ProgramSelectorInterface.h"

class MockUserInput : public UserInputInterface 
{
public:
    bool userButtonIsPressed() override 
    {
        return true; // Simulate button press
    }
};

class MockProgramSelector : public ProgramSelectorInterface 
{
private:
    int selectedProgram = 2;
public:
    void selectNextProgram() override 
    {
        selectedProgram++;
    }

    int getSelectedProgram() const 
    {
        return selectedProgram;
    }
};

class MockMidiController : public MidiControllerInterface 
{
private:
    bool programChangeIsSent = false;

public:
    void sendProgramChange(int program) override 
    {
        programChangeIsSent = true;
    }

    bool getProgramChangeIsSent() 
    {
        return programChangeIsSent;
    }
};

// =================================================================

void setUp(void) 
{
    // Called before each test
}

void tearDown(void) 
{
    // Called after each test
}

// Test that tick() method can be called without error
void testShouldSupportTickMethod(void) 
{
    MidiPatchBoxApplication app;

    app.tick();
}

void testShouldSelectNextProgramOnUserButtonPress(void) 
{
    MidiPatchBoxApplication app;
    
    MockUserInput userInput;
    MockProgramSelector programSelector;

    app.setUserInput(&userInput)
       ->setProgramSelector(&programSelector);
    
    app.tick();

    TEST_ASSERT_EQUAL_INT16(3, programSelector.getSelectedProgram());
}

void testShouldSendProgramChangeOnUserButtonPress(void) 
{
    MidiPatchBoxApplication app;

    MockUserInput userInput;
    MockMidiController midiController;
    MockProgramSelector programSelector;

    app.setUserInput(&userInput)
       ->setMidiController(&midiController)
       ->setProgramSelector(&programSelector);

    app.tick();

    TEST_ASSERT_TRUE(midiController.getProgramChangeIsSent());
}

int main(void) 
{
    UNITY_BEGIN();

    RUN_TEST(testShouldSupportTickMethod);
    RUN_TEST(testShouldSelectNextProgramOnUserButtonPress);
    RUN_TEST(testShouldSendProgramChangeOnUserButtonPress);

    return UNITY_END();
}

#include "unity.h"
#include "app/MidiPatchBoxApplication.h"
#include "app/UserInputInterface.h"
#include "app/ProgramSelectorInterface.h"

class MockUserInput : public UserInputInterface 
{
public:
    bool userButtonIsPressed() override 
    {
        return userButtonPressed; // Simulate button press
    }

    bool rightButtonIsPressed() override
    {
        return rightButtonPressed;
    }

    void pressUserButton() 
    {
        userButtonPressed = true;
    }

    void pressRightButton()
    {
        rightButtonPressed = true;
    }
private:
    bool userButtonPressed = false;
    bool rightButtonPressed = false;
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

    int getSelectedProgramNumber() const 
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

    userInput.pressUserButton();

    app.setUserInput(&userInput)
       ->setProgramSelector(&programSelector);
    
    app.tick();

    TEST_ASSERT_EQUAL_INT16(3, programSelector.getSelectedProgramNumber());
}

void testShouldSendProgramChangeOnUserButtonPress(void) 
{
    MidiPatchBoxApplication app;

    MockUserInput userInput;
    MockMidiController midiController;
    MockProgramSelector programSelector;

    userInput.pressUserButton();

    app.setUserInput(&userInput)
       ->setMidiController(&midiController)
       ->setProgramSelector(&programSelector);

    app.tick();

    TEST_ASSERT_TRUE(midiController.getProgramChangeIsSent());
}

void testShouldSelectNextProgramOnRightButtonPress(void) 
{
    MidiPatchBoxApplication app;
    
    MockUserInput userInput;
    MockProgramSelector programSelector;
    
    userInput.pressRightButton();
    
    app.setUserInput(&userInput)
    ->setProgramSelector(&programSelector);
    
    app.tick();
    
    TEST_ASSERT_EQUAL_INT16(3, programSelector.getSelectedProgramNumber());
}

void testShouldSendProgramChangeOnRightButtonPress(void) 
{
    MidiPatchBoxApplication app;

    MockUserInput userInput;
    MockMidiController midiController;
    MockProgramSelector programSelector;

    userInput.pressRightButton();

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
    RUN_TEST(testShouldSelectNextProgramOnRightButtonPress);
    RUN_TEST(testShouldSendProgramChangeOnRightButtonPress);

    return UNITY_END();
}

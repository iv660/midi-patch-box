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
    void update() override 
    {
        updateCalled = true;
    }

    bool getUpdateCalled() const
    {
        return updateCalled;
    }

private:
    bool userButtonPressed = false;
    bool rightButtonPressed = false;
    bool updateCalled = false;
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

    int getSelectedProgramNumber() const override
    {
        return selectedProgram;
    }

    ProgramSelectorInterface* setPrograms(std::initializer_list<int> programs) override
    {
        return nullptr;
    }
};

class MockMidiController : public MidiControllerInterface 
{
private:
    bool programChangeIsSent = false;
    bool isInitialized = false;

public:
    void sendProgramChange(int program) override 
    {
        programChangeIsSent = true;
    }

    bool getProgramChangeIsSent() 
    {
        return programChangeIsSent;
    }

    void begin() override
    {
        isInitialized = true;
    }

    bool hasBeenInitialized() const
    {
        return isInitialized;
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

void testShouldCallUserInputUpdate(void) 
{
    MidiPatchBoxApplication app;

    MockUserInput userInput;
    app.setUserInput(&userInput);

    app.tick();

    TEST_ASSERT_TRUE(userInput.getUpdateCalled());
}

void testShouldInitializeMidiController(void) 
{
    MidiPatchBoxApplication app;

    MockMidiController midiController;
    app.setMidiController(&midiController);

    app.begin();

    TEST_ASSERT_TRUE(midiController.hasBeenInitialized());
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
    RUN_TEST(testShouldInitializeMidiController);
    RUN_TEST(testShouldSelectNextProgramOnUserButtonPress);
    RUN_TEST(testShouldSendProgramChangeOnUserButtonPress);
    RUN_TEST(testShouldSelectNextProgramOnRightButtonPress);
    RUN_TEST(testShouldSendProgramChangeOnRightButtonPress);
    RUN_TEST(testShouldCallUserInputUpdate);

    return UNITY_END();
}

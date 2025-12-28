#include "unity.h"
#include "app/MidiPatchBoxApplication.h"
#include "app/UserInputInterface.h"
#include "app/ProgramSelectorInterface.h"
#include "app/ProgramSelectionViewInterface.h"
#include "app/StateMachine.h"

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

class MockProgramSelectionView : public ProgramSelectionViewInterface
{
private:
    int lastProgramNumber = -1;

public:
    ProgramSelectionViewInterface* setSelectedProgramNumber(int programNumber) override
    {
        lastProgramNumber = programNumber;
        return this;
    }

    ProgramSelectionViewInterface* displayProgramName(const char* programName) override
    {
        // Simple implementation for testing - just return this
        return this;
    }

    int getLastProgramNumber() const
    {
        return lastProgramNumber;
    }
};

// Mock State for testing StateMachine
class MockStateForStateMachine : public State {
private:
    bool updateCalled = false;

public:
    void enter() override {}
    void exit() override {}
    
    void update() override {
        updateCalled = true;
    }

    bool updateWasCalled() const {
        return updateCalled;
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

void testShouldSetProgramSelectionView(void)
{
    MidiPatchBoxApplication app;
    MockProgramSelectionView mockView;

    MidiPatchBoxApplication* result = app.setProgramSelectionView(&mockView);

    TEST_ASSERT_EQUAL_PTR(&app, result);
}

void testShouldUpdateViewWhenProgramChanges(void)
{
    MidiPatchBoxApplication app;
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;

    // Setup: button pressed, all components configured
    userInput.pressUserButton();
    
    app.setUserInput(&userInput)
       ->setProgramSelector(&programSelector)
       ->setMidiController(&midiController)
       ->setProgramSelectionView(&mockView);

    // Action: tick() processes button press
    app.tick();

    // Assert: view received the selected program number for display
    TEST_ASSERT_EQUAL_INT16(3, mockView.getLastProgramNumber()); // MockProgramSelector returns 3
}

void testShouldNotCrashWhenViewIsNull(void)
{
    MidiPatchBoxApplication app;
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;

    // Setup: no view set, button pressed
    userInput.pressUserButton();
    
    app.setUserInput(&userInput)
       ->setProgramSelector(&programSelector)
       ->setMidiController(&midiController);
    // Note: deliberately NOT setting programSelectionView

    // Action: tick() processes button press
    app.tick();

    // Assert: no crash occurred (test passes if we reach here)
    TEST_ASSERT_TRUE(true);
}

void testShouldDelegateTickToStateMachine(void)
{
    MidiPatchBoxApplication app;
    StateMachine stateMachine;
    MockStateForStateMachine* mockState = new MockStateForStateMachine();
    
    stateMachine.changeState(mockState);
    app.setStateMachine(&stateMachine);
    
    app.tick();
    
    TEST_ASSERT_TRUE(mockState->updateWasCalled());
}

void testShouldWorkWithoutStateMachine(void)
{
    MockUserInput mockUserInput;
    MockProgramSelector mockProgramSelector;
    MockProgramSelectionView mockView;
    MockMidiController mockMidiController;
    
    MidiPatchBoxApplication app;
    app.setUserInput(&mockUserInput);
    app.setProgramSelector(&mockProgramSelector);
    app.setProgramSelectionView(&mockView);
    app.setMidiController(&mockMidiController);
    
    // No StateMachine set - should work in legacy mode
    app.tick();
    
    TEST_ASSERT_TRUE(mockUserInput.getUpdateCalled());
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
    RUN_TEST(testShouldSetProgramSelectionView);
    RUN_TEST(testShouldUpdateViewWhenProgramChanges);
    RUN_TEST(testShouldNotCrashWhenViewIsNull);
    RUN_TEST(testShouldDelegateTickToStateMachine);
    RUN_TEST(testShouldWorkWithoutStateMachine);

    return UNITY_END();
}

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

    bool encoderRotatedClockwise() override { return false; }
    bool encoderRotatedCounterClockwise() override { return false; }
    bool encoderButtonPressed() override { return false; }
    bool encoderButtonLongPressed() override { return false; }

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

    ProgramSelectionViewInterface* highlightProgram() override
    {
        // Simple implementation for testing - just return this
        return this;
    }

    ProgramSelectionViewInterface* clearHighlight() override
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

void testShouldInitializeMidiController(void) 
{
    MidiPatchBoxApplication app;

    MockMidiController midiController;
    app.setMidiController(&midiController);

    app.begin();

    TEST_ASSERT_TRUE(midiController.hasBeenInitialized());
}

void testShouldSetProgramSelectionView(void)
{
    MidiPatchBoxApplication app;
    MockProgramSelectionView mockView;

    MidiPatchBoxApplication* result = app.setProgramSelectionView(&mockView);

    TEST_ASSERT_EQUAL_PTR(&app, result);
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


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(testShouldSupportTickMethod);
    RUN_TEST(testShouldInitializeMidiController);
    RUN_TEST(testShouldSetProgramSelectionView);
    RUN_TEST(testShouldDelegateTickToStateMachine);

    return UNITY_END();
}

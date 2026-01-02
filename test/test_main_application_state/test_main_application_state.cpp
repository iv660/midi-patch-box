#include "unity.h"
#include "app/MainApplicationState.h"
#include "app/UserInputInterface.h"
#include "app/ProgramSelectorInterface.h"
#include "app/MidiControllerInterface.h"
#include "app/ProgramSelectionViewInterface.h"
#include "app/ProgramsBankInterface.h"
#include <cstring>

class MockUserInput : public UserInputInterface
{
public:
    bool userButtonIsPressed() override
    {
        return userButtonPressed;
    }

    bool rightButtonIsPressed() override
    {
        return rightButtonPressed;
    }

    bool encoderRotatedClockwise() override
    {
        return encoderClockwise;
    }

    bool encoderRotatedCounterClockwise() override
    {
        return encoderCounterClockwise;
    }

    bool encoderButtonPressed() override
    {
        return encoderButtonPress;
    }

    void pressUserButton()
    {
        userButtonPressed = true;
    }

    void pressRightButton()
    {
        rightButtonPressed = true;
    }

    void pressEncoderButton()
    {
        encoderButtonPress = true;
    }

    void rotateEncoderClockwise()
    {
        encoderClockwise = true;
    }
    
    void rotateCounterClockwise()
    {
        encoderCounterClockwise = true;
    }
    
    void update() override
    {
        updateCalled = true;
    }

    bool updateWasCalled() const
    {
        return updateCalled;
    }

private:
    bool userButtonPressed = false;
    bool rightButtonPressed = false;
    bool encoderClockwise = false;
    bool encoderCounterClockwise = false;
    bool encoderButtonPress = false;
    bool updateCalled = false;
};

class MockProgramSelector : public ProgramSelectorInterface
{
private:
    int selectedProgram = 2;
    bool nextProgramSelected = false;
    bool previousProgramSelected = false;
    
public:
    void selectNextProgram() override
    {
        selectedProgram++;
        nextProgramSelected = true;
    }

    void selectPreviousProgram() override
    {
        selectedProgram--;
        previousProgramSelected = true;
    }

    int getSelectedProgramNumber() const override
    {
        return selectedProgram;
    }

    ProgramSelectorInterface* setPrograms(std::initializer_list<int> programs) override
    {
        return nullptr;
    }

    bool nextProgramWasSelected() const
    {
        return nextProgramSelected;
    }

    bool previousProgramWasSelected() const
    {
        return previousProgramSelected;
    }

    void reset()
    {
        nextProgramSelected = false;
        previousProgramSelected = false;
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

    bool programChangeWasSent()
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

    void reset()
    {
        programChangeIsSent = false;
    }
};

class MockProgramSelectionView : public ProgramSelectionViewInterface
{
private:
    int lastProgramNumber = -1;
    char lastProgramName[17] = "";
    bool programHighlighted = false;

public:
    ProgramSelectionViewInterface* setSelectedProgramNumber(int programNumber) override
    {
        lastProgramNumber = programNumber;
        return this;
    }

    ProgramSelectionViewInterface* displayProgramName(const char* programName) override
    {
        strncpy(lastProgramName, programName, 16);
        lastProgramName[16] = '\0';
        return this;
    }

    ProgramSelectionViewInterface* highlightProgram() override
    {
        programHighlighted = true;
        return this;
    }

    ProgramSelectionViewInterface* clearHighlight() override
    {
        programHighlighted = false;
        return this;
    }

    int getLastProgramNumber() const
    {
        return lastProgramNumber;
    }

    const char* getLastProgramName() const
    {
        return lastProgramName;
    }

    bool programWasHighlighted() const
    {
        return programHighlighted;
    }

    void resetHighlight()
    {
        programHighlighted = false;
    }
};

class MockProgramsBank : public ProgramsBankInterface
{
public:
    ProgramsBankInterface* addProgram(int programNumber, const char* programName) override
    {
        return this;
    }

    const char* getProgramName(int programNumber) override
    {
        if (programNumber == 2) {
            return "Cello";
        }

        // Return "Viola" for program 3 as expected by the test
        if (programNumber == 3) {
            return "Viola";
        }
        return "Unknown";
    }
};

void setUp(void) 
{
    // Called before each test
}

void tearDown(void) 
{
    // Called after each test
}

void testMainApplicationStateCallsUserInputUpdate(void)
{
    MockUserInput userInput;
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(nullptr)
             ->setMidiController(nullptr)
             ->setProgramSelectionView(nullptr);

    mainState.update();

    TEST_ASSERT_TRUE(userInput.updateWasCalled());
}

void testMainApplicationStateSelectsNextProgramOnUserButtonPress(void)
{
    MockUserInput userInput;
    MockProgramSelector programSelector;

    userInput.pressUserButton();

    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(nullptr)
             ->setProgramSelectionView(nullptr);
    
    mainState.update();

    TEST_ASSERT_EQUAL_INT16(3, programSelector.getSelectedProgramNumber());
}

void testMainApplicationStateSendsProgramChangeOnUserButtonPress(void)
{
    MockUserInput userInput;
    MockMidiController midiController;
    MockProgramSelector programSelector;

    userInput.pressUserButton();

    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(nullptr);

    mainState.update();

    TEST_ASSERT_TRUE(midiController.programChangeWasSent());
}

void testMainApplicationStateSelectsNextProgramOnRightButtonPress(void)
{
    MockUserInput userInput;
    MockProgramSelector programSelector;
    
    userInput.pressRightButton();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(nullptr)
             ->setProgramSelectionView(nullptr);
    
    mainState.update();
    
    TEST_ASSERT_EQUAL_INT16(3, programSelector.getSelectedProgramNumber());
}

void testMainApplicationStateSendsProgramChangeOnRightButtonPress(void)
{
    MockUserInput userInput;
    MockMidiController midiController;
    MockProgramSelector programSelector;

    userInput.pressRightButton();

    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(nullptr);

    mainState.update();

    TEST_ASSERT_TRUE(midiController.programChangeWasSent());
}

void testMainApplicationStateUpdatesViewWhenProgramChanges(void)
{
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    userInput.pressUserButton();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    mainState.update();

    TEST_ASSERT_EQUAL_INT16(3, mockView.getLastProgramNumber());
    TEST_ASSERT_EQUAL_STRING("Viola", mockView.getLastProgramName());
}

void testViewIsUpdatedWithCurrentlySelectedProgramOnEnter(void) {
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    userInput.pressUserButton();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    mainState.enter();

    TEST_ASSERT_EQUAL_INT16(2, mockView.getLastProgramNumber());
    TEST_ASSERT_EQUAL_STRING("Cello", mockView.getLastProgramName());
}

void testInitialProgramShouldBeSentOnEnter(void) {
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    mainState.enter();

    TEST_ASSERT_TRUE(midiController.programChangeWasSent());
}

void testEncoderClockwiseSelectsNextProgramWithoutSendingMidi(void) {
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    userInput.rotateEncoderClockwise();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    mainState.update();

    // Should select next program
    TEST_ASSERT_TRUE(programSelector.nextProgramWasSelected());
    // But should NOT send MIDI
    TEST_ASSERT_FALSE(midiController.programChangeWasSent());
}

void testEncoderButtonPressSendsMidi(void) {
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    userInput.pressEncoderButton();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    mainState.update();

    // Should send MIDI for currently selected program
    TEST_ASSERT_TRUE(midiController.programChangeWasSent());
}

void testViewHighlightsProgramWhenMidiSent(void) {
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    userInput.pressUserButton();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    mainState.update();

    // Should highlight program when MIDI is sent
    TEST_ASSERT_TRUE(mockView.programWasHighlighted());
}

void testEncoderCounterClockwiseSelectsPreviousProgramWithoutSendingMidi(void) {
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    userInput.rotateCounterClockwise();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    mainState.update();

    // Should select previous program
    TEST_ASSERT_TRUE(programSelector.previousProgramWasSelected());
    // But should NOT send MIDI
    TEST_ASSERT_FALSE(midiController.programChangeWasSent());
}

void testEncoderRotationClearsHighlightAfterMidiSent(void) {
    MockUserInput userInput;
    MockProgramSelector programSelector;
    MockMidiController midiController;
    MockProgramSelectionView mockView;
    MockProgramsBank mockProgramsBank;

    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView)
             ->setProgramsBank(&mockProgramsBank);

    // First: send MIDI by pressing button
    userInput.pressUserButton();
    mainState.update();
    TEST_ASSERT_TRUE(mockView.programWasHighlighted());
    
    // Then: rotate encoder (should clear highlight)
    userInput.rotateEncoderClockwise();
    mainState.update();
    
    // Highlight should be cleared (not set again)
    TEST_ASSERT_FALSE(mockView.programWasHighlighted());
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(testMainApplicationStateCallsUserInputUpdate);
    RUN_TEST(testMainApplicationStateSelectsNextProgramOnUserButtonPress);
    RUN_TEST(testMainApplicationStateSendsProgramChangeOnUserButtonPress);
    RUN_TEST(testMainApplicationStateSelectsNextProgramOnRightButtonPress);
    RUN_TEST(testMainApplicationStateSendsProgramChangeOnRightButtonPress);
    RUN_TEST(testMainApplicationStateUpdatesViewWhenProgramChanges);
    RUN_TEST(testViewIsUpdatedWithCurrentlySelectedProgramOnEnter);
    RUN_TEST(testInitialProgramShouldBeSentOnEnter);
    RUN_TEST(testEncoderClockwiseSelectsNextProgramWithoutSendingMidi);
    RUN_TEST(testEncoderButtonPressSendsMidi);
    RUN_TEST(testViewHighlightsProgramWhenMidiSent);
    RUN_TEST(testEncoderCounterClockwiseSelectsPreviousProgramWithoutSendingMidi);
    RUN_TEST(testEncoderRotationClearsHighlightAfterMidiSent);

    return UNITY_END();
}
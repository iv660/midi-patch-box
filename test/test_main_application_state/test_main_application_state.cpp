#include "unity.h"
#include "app/MainApplicationState.h"
#include "app/UserInputInterface.h"
#include "app/ProgramSelectorInterface.h"
#include "app/MidiControllerInterface.h"
#include "app/ProgramSelectionViewInterface.h"

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

    bool updateWasCalled() const
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

    int getLastProgramNumber() const
    {
        return lastProgramNumber;
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

    userInput.pressUserButton();
    
    MainApplicationState mainState;
    mainState.setUserInput(&userInput)
             ->setProgramSelector(&programSelector)
             ->setMidiController(&midiController)
             ->setProgramSelectionView(&mockView);

    mainState.update();

    TEST_ASSERT_EQUAL_INT16(3, mockView.getLastProgramNumber());
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

    return UNITY_END();
}
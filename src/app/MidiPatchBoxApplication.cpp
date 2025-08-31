#include "MidiPatchBoxApplication.h"
#include <stdint.h>

MidiPatchBoxApplication * MidiPatchBoxApplication::setUserInput(UserInputInterface * userInput)
{
    this->userInput = userInput;

    return this;
}

MidiPatchBoxApplication * MidiPatchBoxApplication::setProgramSelector(ProgramSelectorInterface * programSelector)
{
    this->programSelector = programSelector;

    return this;
}

MidiPatchBoxApplication * MidiPatchBoxApplication::setMidiController(MidiControllerInterface * midiController)
{
    this->midiController = midiController;

    return this;
}

void MidiPatchBoxApplication::tick(void)
{
    if (userButtonIsPressed()) {
        handleNextButtonPress();
    }

    if (rightButtonIsPressed()) {
        handleNextButtonPress();
    }
}

bool MidiPatchBoxApplication::userButtonIsPressed(void)
{
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->userButtonIsPressed();
}

bool MidiPatchBoxApplication::rightButtonIsPressed(void)
{
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->rightButtonIsPressed();
}

void MidiPatchBoxApplication::handleNextButtonPress(void)
{
    if (false == hasProgramSelector()) {
        return;
    }

    programSelector->selectNextProgram();

    if (false == hasMidiController()) {
        return;
    }

    int program = programSelector->getSelectedProgramNumber();
    midiController->sendProgramChange(program);
}

bool MidiPatchBoxApplication::hasProgramSelector()
{
    return programSelector != nullptr;
}

bool MidiPatchBoxApplication::hasUserInput()
{
    return userInput != nullptr;
}

bool MidiPatchBoxApplication::hasMidiController()
{
    return midiController != nullptr;
}

#include "MidiPatchBoxApplication.h"

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

void MidiPatchBoxApplication::tick(void)
{
    if (userButtonIsPressed()) {
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

void MidiPatchBoxApplication::handleNextButtonPress(void)
{
    if (false == hasProgramSelector()) {
        return;
    }

    programSelector->selectNextProgram();
}

bool MidiPatchBoxApplication::hasProgramSelector()
{
    return programSelector != nullptr;
}

bool MidiPatchBoxApplication::hasUserInput()
{
    return userInput != nullptr;
}

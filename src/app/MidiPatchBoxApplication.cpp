#include "MidiPatchBoxApplication.h"
#include <stdint.h>

void MidiPatchBoxApplication::begin(void)
{
    if (hasMidiController()) {
        midiController->begin();
    }
}

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

MidiPatchBoxApplication * MidiPatchBoxApplication::setProgramSelectionView(ProgramSelectionViewInterface * programSelectionView)
{
    this->programSelectionView = programSelectionView;

    return this;
}

void MidiPatchBoxApplication::tick(void)
{
    if (hasUserInput()) {
        userInput->update();
    }

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

    // Update view with selected program number
    if (hasProgramSelectionView()) {
        programSelectionView->setSelectedProgramNumber(program);
    }
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

bool MidiPatchBoxApplication::hasProgramSelectionView()
{
    return programSelectionView != nullptr;
}

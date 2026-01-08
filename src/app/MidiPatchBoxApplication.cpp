#include "MidiPatchBoxApplication.h"
#include "StateMachine.h"
#include <stdint.h>

void MidiPatchBoxApplication::begin(void)
{
    if (hasMidiController()) {
        getMidiController()->begin();
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

MidiPatchBoxApplication * MidiPatchBoxApplication::setStateMachine(StateMachine * stateMachine)
{
    this->stateMachine = stateMachine;

    return this;
}

MidiPatchBoxApplication * MidiPatchBoxApplication::setDiContainer(DiContainerInterface * diContainer)
{
    this->diContainer = diContainer;

    return this;
}

void MidiPatchBoxApplication::tick(void)
{
    if (getStateMachine()) {
        getStateMachine()->update();
    }
}

bool MidiPatchBoxApplication::hasMidiController()
{
    return getMidiController() != nullptr;
}

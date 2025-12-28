#pragma once
#include "StateFactory.h"
#include "MainApplicationState.h"
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"

class MainApplicationStateFactory : public StateFactory {
private:
    UserInputInterface* userInput;
    ProgramSelectorInterface* programSelector;
    MidiControllerInterface* midiController;
    ProgramSelectionViewInterface* programSelectionView;

public:
    MainApplicationStateFactory(
        UserInputInterface* userInput,
        ProgramSelectorInterface* programSelector,
        MidiControllerInterface* midiController,
        ProgramSelectionViewInterface* programSelectionView
    ) : userInput(userInput), 
        programSelector(programSelector), 
        midiController(midiController), 
        programSelectionView(programSelectionView) {}

    StateInterface* createMainApplicationState() override {
        return new MainApplicationState(userInput, programSelector, midiController, programSelectionView);
    }
};
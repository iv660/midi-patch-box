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
    MainApplicationStateFactory() = default;
    
    MainApplicationStateFactory* setUserInput(UserInputInterface* userInput) {
        this->userInput = userInput;
        return this;
    }
    
    MainApplicationStateFactory* setProgramSelector(ProgramSelectorInterface* programSelector) {
        this->programSelector = programSelector;
        return this;
    }
    
    MainApplicationStateFactory* setMidiController(MidiControllerInterface* midiController) {
        this->midiController = midiController;
        return this;
    }
    
    MainApplicationStateFactory* setProgramSelectionView(ProgramSelectionViewInterface* programSelectionView) {
        this->programSelectionView = programSelectionView;
        return this;
    }

    StateInterface* createMainApplicationState() override {
        return (new MainApplicationState())
            ->setUserInput(userInput)
            ->setProgramSelector(programSelector)
            ->setMidiController(midiController)
            ->setProgramSelectionView(programSelectionView);
    }
};
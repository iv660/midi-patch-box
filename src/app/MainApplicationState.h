#pragma once
#include "State.h"
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"
#include "ProgramsBankInterface.h"

class MainApplicationState : public State {
private:
    UserInputInterface* userInput = nullptr;
    ProgramSelectorInterface* programSelector = nullptr;
    MidiControllerInterface* midiController = nullptr;
    ProgramSelectionViewInterface* programSelectionView = nullptr;
    ProgramsBankInterface* programsBank = nullptr;

    bool userButtonIsPressed();
    bool rightButtonIsPressed();
    void handleNextButtonPress();
    bool hasProgramSelector();
    bool hasUserInput();
    bool hasMidiController();
    bool hasProgramSelectionView();
    bool hasProgramsBank();

public:
    MainApplicationState() = default;
    
    MainApplicationState* setUserInput(UserInputInterface* userInput) {
        this->userInput = userInput;
        return this;
    }
    
    MainApplicationState* setProgramSelector(ProgramSelectorInterface* programSelector) {
        this->programSelector = programSelector;
        return this;
    }
    
    MainApplicationState* setMidiController(MidiControllerInterface* midiController) {
        this->midiController = midiController;
        return this;
    }
    
    MainApplicationState* setProgramSelectionView(ProgramSelectionViewInterface* programSelectionView) {
        this->programSelectionView = programSelectionView;
        return this;
    }
    
    MainApplicationState* setProgramsBank(ProgramsBankInterface* programsBank) {
        this->programsBank = programsBank;
        return this;
    }
    
    void enter() override;
    void update() override;
    void exit() override;
};
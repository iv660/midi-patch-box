#pragma once
#include "State.h"
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"

class MainApplicationState : public State {
private:
    UserInputInterface* userInput = nullptr;
    ProgramSelectorInterface* programSelector = nullptr;
    MidiControllerInterface* midiController = nullptr;
    ProgramSelectionViewInterface* programSelectionView = nullptr;

    bool userButtonIsPressed();
    bool rightButtonIsPressed();
    void handleNextButtonPress();
    bool hasProgramSelector();
    bool hasUserInput();
    bool hasMidiController();
    bool hasProgramSelectionView();

public:
    MainApplicationState(UserInputInterface* userInput, 
                        ProgramSelectorInterface* programSelector,
                        MidiControllerInterface* midiController,
                        ProgramSelectionViewInterface* programSelectionView);
    
    void enter() override;
    void update() override;
    void exit() override;
};
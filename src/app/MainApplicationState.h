#pragma once
#include "State.h"
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"
#include "ProgramsBankInterface.h"
#include "StateFactoryInterface.h"
#include "StateMachineInterface.h"

class MainApplicationState : public State {
private:
    UserInputInterface* userInput = nullptr;
    ProgramSelectorInterface* programSelector = nullptr;
    MidiControllerInterface* midiController = nullptr;
    ProgramSelectionViewInterface* programSelectionView = nullptr;
    ProgramsBankInterface* programsBank = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    int lastSentProgram = -1;

    bool userButtonIsPressed();
    bool rightButtonIsPressed();
    bool encoderRotatedClockwise();
    bool encoderRotatedCounterClockwise();
    bool encoderButtonPressed();
    bool encoderButtonLongPressed();
    void handleNextButtonPress();
    void handleEncoderRotation();
    void handleEncoderButtonPress();
    void handleEncoderButtonLongPress();
    void selectNextProgram();
    void selectPreviousProgram();
    void sendSelectedProgram();
    void updateProgramSelectionView();
    void changeToConfigMenuState();
    bool hasProgramSelector();
    bool hasUserInput();
    bool hasMidiController();
    bool hasProgramSelectionView();
    bool hasProgramsBank();
    bool hasStateFactory();
    bool hasStateMachine();

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
    
    MainApplicationState* setStateFactory(StateFactoryInterface* stateFactory) {
        this->stateFactory = stateFactory;
        return this;
    }
    
    void enter() override;
    void update() override;
    void exit() override;
};
#pragma once
#include "StateFactoryInterface.h"
#include "MainApplicationState.h"
#include "ConfigMenuState.h"
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"
#include "ProgramsBankInterface.h"
#include "ConfigMenuViewInterface.h"
#include "StateMachineInterface.h"

class StateFactory : public StateFactoryInterface {
private:
    UserInputInterface* userInput = nullptr;
    ProgramSelectorInterface* programSelector = nullptr;
    MidiControllerInterface* midiController = nullptr;
    ProgramSelectionViewInterface* programSelectionView = nullptr;
    ProgramsBankInterface* programsBank = nullptr;
    ConfigMenuViewInterface* configMenuView = nullptr;
    StateMachineInterface* stateMachine = nullptr;

public:
    StateFactory() = default;
    virtual ~StateFactory() = default;
    
    StateFactory* setUserInput(UserInputInterface* userInput) {
        this->userInput = userInput;
        return this;
    }
    
    StateFactory* setProgramSelector(ProgramSelectorInterface* programSelector) {
        this->programSelector = programSelector;
        return this;
    }
    
    StateFactory* setMidiController(MidiControllerInterface* midiController) {
        this->midiController = midiController;
        return this;
    }
    
    StateFactory* setProgramSelectionView(ProgramSelectionViewInterface* programSelectionView) {
        this->programSelectionView = programSelectionView;
        return this;
    }
    
    StateFactory* setProgramsBank(ProgramsBankInterface* programsBank) {
        this->programsBank = programsBank;
        return this;
    }
    
    StateFactory* setConfigMenuView(ConfigMenuViewInterface* configMenuView) {
        this->configMenuView = configMenuView;
        return this;
    }
    
    StateFactory* setStateMachine(StateMachineInterface* stateMachine) {
        this->stateMachine = stateMachine;
        return this;
    }

    StateInterface* createMainApplicationState() override {
        return (new MainApplicationState())
            ->setUserInput(userInput)
            ->setProgramSelector(programSelector)
            ->setMidiController(midiController)
            ->setProgramSelectionView(programSelectionView)
            ->setProgramsBank(programsBank)
            ->setStateFactory(this)
            ->setStateMachine(stateMachine);
    }
    
    StateInterface* createConfigMenuState() override {
        return (new ConfigMenuState())
            ->setUserInput(userInput)
            ->setConfigMenuView(configMenuView)
            ->setStateFactory(this)
            ->setStateMachine(stateMachine);
    }
    
    StateInterface* createEditSetlistState() override {
        // TODO: Implement EditSetlistState
        return nullptr;
    }
};
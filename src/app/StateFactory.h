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
#include "DiContainerInterface.h"

class StateFactory : public StateFactoryInterface {
private:
    UserInputInterface* userInput = nullptr;
    ProgramSelectorInterface* programSelector = nullptr;
    MidiControllerInterface* midiController = nullptr;
    ProgramSelectionViewInterface* programSelectionView = nullptr;
    ProgramsBankInterface* programsBank = nullptr;
    ConfigMenuViewInterface* configMenuView = nullptr;
    StateMachineInterface* stateMachine = nullptr;
    DiContainerInterface* diContainer = nullptr;
    
    // Private getters for lazy dependency resolution
    UserInputInterface* getUserInput() const {
        return userInput ? userInput : (diContainer ? diContainer->getUserInput() : nullptr);
    }
    ProgramSelectorInterface* getProgramSelector() const {
        return programSelector ? programSelector : (diContainer ? diContainer->getProgramSelector() : nullptr);
    }
    MidiControllerInterface* getMidiController() const {
        return midiController ? midiController : (diContainer ? diContainer->getMidiController() : nullptr);
    }
    ProgramSelectionViewInterface* getProgramSelectionView() const {
        return programSelectionView ? programSelectionView : (diContainer ? diContainer->getProgramSelectionView() : nullptr);
    }
    ProgramsBankInterface* getProgramsBank() const {
        return programsBank ? programsBank : (diContainer ? diContainer->getProgramsBank() : nullptr);
    }
    ConfigMenuViewInterface* getConfigMenuView() const {
        return configMenuView ? configMenuView : (diContainer ? diContainer->getConfigMenuView() : nullptr);
    }
    StateMachineInterface* getStateMachine() const {
        return stateMachine ? stateMachine : (diContainer ? diContainer->getStateMachineInterface() : nullptr);
    }

public:
    StateFactory() = default;
    virtual ~StateFactory() = default;
    
    // Constructor with DiContainer for dependency injection
    explicit StateFactory(DiContainerInterface* container) : diContainer(container) {
        // Dependencies will be resolved lazily through getters
    }
    
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
    
    StateFactory* setDiContainer(DiContainerInterface* diContainer) {
        this->diContainer = diContainer;
        return this;
    }

    StateInterface* createMainApplicationState() override {
        return (new MainApplicationState())
            ->setUserInput(getUserInput())
            ->setProgramSelector(getProgramSelector())
            ->setMidiController(getMidiController())
            ->setProgramSelectionView(getProgramSelectionView())
            ->setProgramsBank(getProgramsBank())
            ->setStateFactory(this)
            ->setStateMachine(getStateMachine());
    }
    
    StateInterface* createConfigMenuState() override {
        return (new ConfigMenuState())
            ->setUserInput(getUserInput())
            ->setConfigMenuView(getConfigMenuView())
            ->setStateFactory(this)
            ->setStateMachine(getStateMachine());
    }
    
    StateInterface* createEditSetlistState() override {
        // TODO: Implement EditSetlistState
        return nullptr;
    }
};
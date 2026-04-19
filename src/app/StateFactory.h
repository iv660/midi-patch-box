#pragma once
#include "StateFactoryInterface.h"
#include "MainApplicationState.h"
#include "ConfigMenuState.h"
#include "SetlistMenuState.h"
#include "Context.h"
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
    DiContainerInterface* diContainer = nullptr;
    const Context* context = nullptr;
    
    // Private getters for lazy dependency resolution
    UserInputInterface* getUserInput() const {
        return diContainer 
            ? diContainer->getUserInput() 
            : nullptr;
    }
    ProgramSelectorInterface* getProgramSelector() const {
        return diContainer 
            ? diContainer->getProgramSelector() 
            : nullptr;
    }
    MidiControllerInterface* getMidiController() const {
        return diContainer 
            ? diContainer->getMidiController() 
            : nullptr;
    }
    ProgramSelectionViewInterface* getProgramSelectionView() const {
        return diContainer 
            ? diContainer->getProgramSelectionView() 
            : nullptr;
    }
    ProgramsBankInterface* getProgramsBank() const {
        return diContainer 
            ? diContainer->getProgramsBank() 
            : nullptr;
    }
    ConfigMenuViewInterface* getConfigMenuView() const {
        return diContainer 
            ? diContainer->getConfigMenuView() 
            : nullptr;
    }
    StateMachineInterface* getStateMachine() const {
        return diContainer 
            ? diContainer->getStateMachineInterface() 
            : nullptr;
    }

public:
    StateFactory() = default;
    virtual ~StateFactory() = default;
    
    // Constructor with DiContainer for dependency injection
    explicit StateFactory(DiContainerInterface* container) : diContainer(container) {
        // Dependencies will be resolved lazily through getters
    }

    explicit StateFactory(DiContainerInterface* container, const Context* context)
        : diContainer(container), context(context) {
    }
    
    StateFactory* setDiContainer(DiContainerInterface* diContainer) {
        this->diContainer = diContainer;
        return this;
    }

    StateFactory* setContext(const Context* context) {
        this->context = context;
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
        return new ConfigMenuState(diContainer);
    }
    
    StateInterface* createSetlistMenuState() override {
        return new SetlistMenuState(diContainer, context);
    }
};

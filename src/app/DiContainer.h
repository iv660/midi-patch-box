#pragma once
#include "DiContainerInterface.h"
#include "SplashScreenViewInterface.h"
#include "IoDriverInterface.h"
#include "StateFactoryInterface.h"
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"
#include "ProgramsBankInterface.h"
#include "ConfigMenuViewInterface.h"
#include "StateMachine.h"
#include "StateMachineInterface.h"

class DiContainer : public DiContainerInterface {
private:
    SplashScreenViewInterface* splashScreenView = nullptr;
    IoDriverInterface* ioDriver = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    UserInputInterface* userInput = nullptr;
    ProgramSelectorInterface* programSelector = nullptr;
    MidiControllerInterface* midiController = nullptr;
    ProgramSelectionViewInterface* programSelectionView = nullptr;
    StateMachine* stateMachine = nullptr;
    ProgramsBankInterface* programsBank = nullptr;
    ConfigMenuViewInterface* configMenuView = nullptr;

public:
    DiContainer() = default;
    virtual ~DiContainer() = default;
    
    // Setters for SplashScreenState dependencies
    DiContainer* setSplashScreenView(SplashScreenViewInterface* view) {
        this->splashScreenView = view;
        return this;
    }
    
    DiContainer* setIoDriver(IoDriverInterface* driver) {
        this->ioDriver = driver;
        return this;
    }
    
    DiContainer* setStateFactory(StateFactoryInterface* factory) {
        this->stateFactory = factory;
        return this;
    }
    
    // Setters for MidiPatchBoxApplication dependencies
    DiContainer* setUserInput(UserInputInterface* input) {
        this->userInput = input;
        return this;
    }
    
    DiContainer* setProgramSelector(ProgramSelectorInterface* selector) {
        this->programSelector = selector;
        return this;
    }
    
    DiContainer* setMidiController(MidiControllerInterface* controller) {
        this->midiController = controller;
        return this;
    }
    
    DiContainer* setProgramSelectionView(ProgramSelectionViewInterface* view) {
        this->programSelectionView = view;
        return this;
    }
    
    DiContainer* setStateMachine(StateMachine* machine) {
        this->stateMachine = machine;
        return this;
    }
    
    // Setters for StateFactory dependencies
    DiContainer* setProgramsBank(ProgramsBankInterface* bank) {
        this->programsBank = bank;
        return this;
    }
    
    DiContainer* setConfigMenuView(ConfigMenuViewInterface* view) {
        this->configMenuView = view;
        return this;
    }
    
    // Getters for SplashScreenState dependencies
    SplashScreenViewInterface* getSplashScreenView() const override {
        return splashScreenView;
    }
    
    IoDriverInterface* getIoDriver() const override {
        return ioDriver;
    }
    
    StateFactoryInterface* getStateFactory() const override {
        return stateFactory;
    }
    
    // Getters for MidiPatchBoxApplication dependencies
    UserInputInterface* getUserInput() const override {
        return userInput;
    }
    
    ProgramSelectorInterface* getProgramSelector() const override {
        return programSelector;
    }
    
    MidiControllerInterface* getMidiController() const override {
        return midiController;
    }
    
    ProgramSelectionViewInterface* getProgramSelectionView() const override {
        return programSelectionView;
    }
    
    StateMachine* getStateMachine() const override {
        return stateMachine;
    }
    
    // Getters for StateFactory dependencies
    ProgramsBankInterface* getProgramsBank() const override {
        return programsBank;
    }
    
    ConfigMenuViewInterface* getConfigMenuView() const override {
        return configMenuView;
    }
    
    StateMachineInterface* getStateMachineInterface() const override {
        return stateMachine; // StateMachine implements StateMachineInterface
    }
};
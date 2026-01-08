#pragma once

// Forward declarations
class SplashScreenViewInterface;
class IoDriverInterface;
class StateFactoryInterface;
class UserInputInterface;
class ProgramSelectorInterface;
class MidiControllerInterface;
class ProgramSelectionViewInterface;
class ProgramsBankInterface;
class ConfigMenuViewInterface;
class StateMachine;
class StateMachineInterface;

class DiContainerInterface {
public:
    virtual ~DiContainerInterface() = default;
    
    // Dependencies for SplashScreenState
    virtual SplashScreenViewInterface* getSplashScreenView() const = 0;
    virtual IoDriverInterface* getIoDriver() const = 0;
    virtual StateFactoryInterface* getStateFactory() const = 0;
    
    // Dependencies for MidiPatchBoxApplication
    virtual UserInputInterface* getUserInput() const = 0;
    virtual ProgramSelectorInterface* getProgramSelector() const = 0;
    virtual MidiControllerInterface* getMidiController() const = 0;
    virtual ProgramSelectionViewInterface* getProgramSelectionView() const = 0;
    virtual StateMachine* getStateMachine() const = 0;
    
    // Dependencies for StateFactory
    virtual ProgramsBankInterface* getProgramsBank() const = 0;
    virtual ConfigMenuViewInterface* getConfigMenuView() const = 0;
    virtual StateMachineInterface* getStateMachineInterface() const = 0;
};
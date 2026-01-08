#pragma once

// Forward declarations
class SplashScreenViewInterface;
class IoDriverInterface;
class StateFactoryInterface;
class UserInputInterface;
class ProgramSelectorInterface;
class MidiControllerInterface;
class ProgramSelectionViewInterface;
class StateMachine;

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
};
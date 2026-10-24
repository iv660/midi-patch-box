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
class EditSetlistViewInterface;
class MenuControllerInterface;
class MenuLayoutViewInterface;
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
    virtual StateMachineInterface* getStateMachine() const = 0;
    
    // Dependencies for StateFactory
    virtual ProgramsBankInterface* getProgramsBank() const = 0;
    virtual ConfigMenuViewInterface* getConfigMenuView() const = 0;
    virtual EditSetlistViewInterface* getEditSetlistView() const = 0;
    
    // Dependencies for SetlistMenuState
    virtual MenuControllerInterface* getSetlistMenuController() const = 0;
    virtual MenuLayoutViewInterface* getSetlistMenuLayoutView() const = 0;
    
    /**
     * @deprecated Use getStateMachine()
     */
    virtual StateMachineInterface* getStateMachineInterface() const = 0;
};
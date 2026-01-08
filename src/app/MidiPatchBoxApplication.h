#pragma once
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"
#include "DiContainerInterface.h"

// Forward declaration to avoid circular dependency
class StateMachine;

class MidiPatchBoxApplication {
private:
    UserInputInterface *userInput = nullptr;
    ProgramSelectorInterface *programSelector = nullptr;
    MidiControllerInterface *midiController = nullptr;
    ProgramSelectionViewInterface *programSelectionView = nullptr;
    StateMachine *stateMachine = nullptr;

    bool hasMidiController();
public:
    MidiPatchBoxApplication() = default;
    
    // Constructor with DiContainer for dependency injection
    explicit MidiPatchBoxApplication(DiContainerInterface* container) {
        if (!container) return;
        
        userInput = container->getUserInput();
        programSelector = container->getProgramSelector();
        midiController = container->getMidiController();
        programSelectionView = container->getProgramSelectionView();
        stateMachine = container->getStateMachine();
    }
    
    void tick();
    void begin(void);
    
    MidiPatchBoxApplication* setUserInput(UserInputInterface *userInput);
    MidiPatchBoxApplication* setProgramSelector(ProgramSelectorInterface *programSelector);
    MidiPatchBoxApplication* setMidiController(MidiControllerInterface *midiController);
    MidiPatchBoxApplication* setProgramSelectionView(ProgramSelectionViewInterface *programSelectionView);
    MidiPatchBoxApplication* setStateMachine(StateMachine *stateMachine);
};
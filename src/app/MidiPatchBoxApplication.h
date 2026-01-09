#pragma once
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"
#include "DiContainerInterface.h"
#include "StateMachineInterface.h"

// Forward declaration to avoid circular dependency
class StateMachine;

class MidiPatchBoxApplication {
private:
    UserInputInterface *userInput = nullptr;
    ProgramSelectorInterface *programSelector = nullptr;
    MidiControllerInterface *midiController = nullptr;
    ProgramSelectionViewInterface *programSelectionView = nullptr;
    StateMachineInterface *stateMachine = nullptr;
    DiContainerInterface *diContainer = nullptr;

    bool hasMidiController();
    
    // Private getters
    MidiControllerInterface* getMidiController() const {
        return midiController ? midiController : (diContainer ? diContainer->getMidiController() : nullptr);
    }
    StateMachineInterface* getStateMachine() const {
        return stateMachine ? stateMachine : (diContainer ? diContainer->getStateMachine() : nullptr);
    }
    UserInputInterface* getUserInput() const {
        return userInput ? userInput : (diContainer ? diContainer->getUserInput() : nullptr);
    }
    ProgramSelectorInterface* getProgramSelector() const {
        return programSelector ? programSelector : (diContainer ? diContainer->getProgramSelector() : nullptr);
    }
    ProgramSelectionViewInterface* getProgramSelectionView() const {
        return programSelectionView ? programSelectionView : (diContainer ? diContainer->getProgramSelectionView() : nullptr);
    }
public:
    MidiPatchBoxApplication() = default;
    
    // Constructor with DiContainer for dependency injection
    explicit MidiPatchBoxApplication(DiContainerInterface* container) : diContainer(container) {
        // Dependencies will be resolved lazily through getters
    }
    
    void tick();
    void begin(void);
    
    MidiPatchBoxApplication* setUserInput(UserInputInterface *userInput);
    MidiPatchBoxApplication* setProgramSelector(ProgramSelectorInterface *programSelector);
    MidiPatchBoxApplication* setMidiController(MidiControllerInterface *midiController);
    MidiPatchBoxApplication* setProgramSelectionView(ProgramSelectionViewInterface *programSelectionView);
    MidiPatchBoxApplication* setStateMachine(StateMachineInterface *stateMachine);
    MidiPatchBoxApplication* setDiContainer(DiContainerInterface *diContainer);
};
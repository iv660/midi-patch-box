#pragma once
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"
#include "ProgramSelectionViewInterface.h"

class MidiPatchBoxApplication {
private:
    UserInputInterface *userInput = nullptr;
    ProgramSelectorInterface *programSelector = nullptr;
    MidiControllerInterface *midiController = nullptr;
    ProgramSelectionViewInterface *programSelectionView = nullptr;

    bool userButtonIsPressed(void);
    void handleNextButtonPress(void);
    bool hasProgramSelector();
    bool hasUserInput();
    bool hasMidiController();
    bool hasProgramSelectionView();
    bool rightButtonIsPressed(void);
public:
    void tick();
    void begin(void);
    
    MidiPatchBoxApplication* setUserInput(UserInputInterface *userInput);
    MidiPatchBoxApplication* setProgramSelector(ProgramSelectorInterface *programSelector);
    MidiPatchBoxApplication* setMidiController(MidiControllerInterface *midiController);
    MidiPatchBoxApplication* setProgramSelectionView(ProgramSelectionViewInterface *programSelectionView);
};
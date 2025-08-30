#pragma once
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "MidiControllerInterface.h"

class MidiPatchBoxApplication {
private:
    UserInputInterface *userInput = nullptr;
    ProgramSelectorInterface *programSelector = nullptr;
    MidiControllerInterface *midiController = nullptr;

    bool userButtonIsPressed(void);
    void handleNextButtonPress(void);
    bool hasProgramSelector();
    bool hasUserInput();
    bool hasMidiController();
    bool rightButtonIsPressed(void);
public:
    void tick();
    MidiPatchBoxApplication* setUserInput(UserInputInterface *userInput);
    MidiPatchBoxApplication* setProgramSelector(ProgramSelectorInterface *programSelector);
    MidiPatchBoxApplication* setMidiController(MidiControllerInterface *midiController);
};
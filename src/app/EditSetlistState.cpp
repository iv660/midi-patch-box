#include "EditSetlistState.h"
#include "EditSetlistViewInterface.h"
#include "UserInputInterface.h"
#include "ProgramSelectorInterface.h"
#include "ProgramsBankInterface.h"
#include "StateMachineInterface.h"
#include "StateFactoryInterface.h"
#include "Program.h"
#include <cstring>
#include <cstdio>

EditSetlistState::EditSetlistState(DiContainerInterface* container)
    : diContainer(container), stateMachine(nullptr), selectedIndex(0), 
      isEditMode(false), editedProgramNumber(0) {
}

void EditSetlistState::enter() {
    auto view = diContainer->getEditSetlistView();
    auto programsBank = diContainer->getProgramsBank();
    
    // Get all programs from the bank
    int programCount = 0;
    const Program* allPrograms = programsBank->getAllPrograms(programCount);
    
    // Copy programs to current setlist
    for (int i = 0; i < programCount && i < 16; i++) {
        currentSetlist[i] = allPrograms[i];
    }
    
    // Show setlist in view
    view->showSetlist(currentSetlist);
    view->setSelectedItemIndex(selectedIndex);
}

void EditSetlistState::exit() {
    // Cleanup if needed
}

void EditSetlistState::update() {
    auto userInput = diContainer->getUserInput();
    auto view = diContainer->getEditSetlistView();
    auto programsBank = diContainer->getProgramsBank();
    
    if (isEditMode) {
        // Handle edit mode input
        if (userInput->encoderRotatedClockwise()) {
            editedProgramNumber = (editedProgramNumber + 1) % 128;
            view->setEditedProgramNumber(editedProgramNumber);
            const char* name = programsBank->getProgramName(editedProgramNumber);
            if (name) {
                view->setEditedProgramName(name);
            } else {
                char tempName[17];
                snprintf(tempName, 17, "Program %d", editedProgramNumber);
                view->setEditedProgramName(tempName);
            }
        } else if (userInput->encoderRotatedCounterClockwise()) {
            editedProgramNumber = (editedProgramNumber - 1 + 128) % 128;
            view->setEditedProgramNumber(editedProgramNumber);
            const char* name = programsBank->getProgramName(editedProgramNumber);
            if (name) {
                view->setEditedProgramName(name);
            } else {
                char tempName[17];
                snprintf(tempName, 17, "Program %d", editedProgramNumber);
                view->setEditedProgramName(tempName);
            }
        } else if (userInput->encoderButtonPressed()) {
            // Save edited program
            currentSetlist[selectedIndex].number = editedProgramNumber;
            const char* name = programsBank->getProgramName(editedProgramNumber);
            if (name) {
                strncpy(currentSetlist[selectedIndex].name, name, 16);
                currentSetlist[selectedIndex].name[16] = '\0';
            } else {
                snprintf(currentSetlist[selectedIndex].name, 17, "Program %d", editedProgramNumber);
            }
            
            // Update program selector with new program
            auto programSelector = diContainer->getProgramSelector();
            programSelector->updateProgram(selectedIndex, editedProgramNumber);
            
            // Update view and exit edit mode
            view->showSetlist(currentSetlist);
            view->setSelectedItemIndex(selectedIndex);
            view->setEditMode(false);
            isEditMode = false;
        }
    } else {
        // Handle navigation mode input
        if (userInput->encoderRotatedClockwise()) {
            selectedIndex = (selectedIndex + 1) % 16;
            view->setSelectedItemIndex(selectedIndex);
        } else if (userInput->encoderRotatedCounterClockwise()) {
            selectedIndex = (selectedIndex - 1 + 16) % 16;
            view->setSelectedItemIndex(selectedIndex);
        } else if (userInput->encoderButtonPressed()) {
            // Enter edit mode for selected program
            editedProgramNumber = currentSetlist[selectedIndex].number;
            isEditMode = true;
            view->setEditMode(true);
            view->setEditedProgramIndex(selectedIndex);
            view->setEditedProgramNumber(editedProgramNumber);
            const char* name = programsBank->getProgramName(editedProgramNumber);
            if (name) {
                view->setEditedProgramName(name);
            } else {
                char tempName[17];
                snprintf(tempName, 17, "Program %d", editedProgramNumber);
                view->setEditedProgramName(tempName);
            }
        }
    }
}

StateInterface* EditSetlistState::setStateMachine(StateMachineInterface* sm) {
    stateMachine = sm;
    return this;
}
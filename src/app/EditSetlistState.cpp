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
    if (isInEditMode()) {
        handleEditModeInput();
        return;
    }
    
    if (isInNavigationMode()) {
        handleNavigationModeInput();
        return;
    }
}

StateInterface* EditSetlistState::setStateMachine(StateMachineInterface* stateMachine) {
    this->stateMachine = stateMachine;
    return this;
}

// Input condition checking methods
bool EditSetlistState::encoderRotatedClockwise() {
    auto userInput = diContainer->getUserInput();
    return userInput->encoderRotatedClockwise();
}

bool EditSetlistState::encoderRotatedCounterClockwise() {
    auto userInput = diContainer->getUserInput();
    return userInput->encoderRotatedCounterClockwise();
}

bool EditSetlistState::encoderButtonPressed() {
    auto userInput = diContainer->getUserInput();
    return userInput->encoderButtonPressed();
}

// State checking methods
bool EditSetlistState::isInEditMode() const {
    return isEditMode;
}

bool EditSetlistState::isInNavigationMode() const {
    return !isEditMode;
}

// Mode handlers
void EditSetlistState::handleEditModeInput() {
    if (encoderRotatedClockwise()) {
        incrementEditedProgram();
        updateEditedProgramDisplay();
        return;
    }
    
    if (encoderRotatedCounterClockwise()) {
        decrementEditedProgram();
        updateEditedProgramDisplay();
        return;
    }
    
    if (encoderButtonPressed()) {
        handleEditModeButtonPress();
        return;
    }
}

void EditSetlistState::handleNavigationModeInput() {
    if (encoderRotatedClockwise()) {
        moveSelectionUp();
        updateSelectionDisplay();
        return;
    }
    
    if (encoderRotatedCounterClockwise()) {
        moveSelectionDown();
        updateSelectionDisplay();
        return;
    }
    
    if (encoderButtonPressed()) {
        handleNavigationModeButtonPress();
        return;
    }
}

// Edit mode operations
void EditSetlistState::handleEditModeEncoderRotation() {
    if (encoderRotatedClockwise()) {
        incrementEditedProgram();
        return;
    }
    
    if (encoderRotatedCounterClockwise()) {
        decrementEditedProgram();
        return;
    }
}

void EditSetlistState::handleEditModeButtonPress() {
    saveEditedProgram();
    exitEditMode();
}

void EditSetlistState::incrementEditedProgram() {
    editedProgramNumber = (editedProgramNumber + 1) % 128;
}

void EditSetlistState::decrementEditedProgram() {
    editedProgramNumber = (editedProgramNumber - 1 + 128) % 128;
}

void EditSetlistState::updateEditedProgramDisplay() {
    auto view = diContainer->getEditSetlistView();
    view->setEditedProgramNumber(editedProgramNumber);
    
    const char* displayName = getProgramDisplayName(editedProgramNumber);
    view->setEditedProgramName(displayName);
}

void EditSetlistState::saveEditedProgram() {
    updateProgramInSetlist(selectedIndex, editedProgramNumber);
    
    auto programSelector = diContainer->getProgramSelector();
    programSelector->updateProgram(selectedIndex, editedProgramNumber);
}

void EditSetlistState::exitEditMode() {
    isEditMode = false;
    updateViewAfterEdit();
}

// Navigation mode operations
void EditSetlistState::handleNavigationModeEncoderRotation() {
    if (encoderRotatedClockwise()) {
        moveSelectionUp();
        return;
    }
    
    if (encoderRotatedCounterClockwise()) {
        moveSelectionDown();
        return;
    }
}

void EditSetlistState::handleNavigationModeButtonPress() {
    enterEditMode();
}

void EditSetlistState::moveSelectionUp() {
    selectedIndex = (selectedIndex + 1) % 16;
}

void EditSetlistState::moveSelectionDown() {
    selectedIndex = (selectedIndex - 1 + 16) % 16;
}

void EditSetlistState::updateSelectionDisplay() {
    auto view = diContainer->getEditSetlistView();
    view->setSelectedItemIndex(selectedIndex);
}

void EditSetlistState::enterEditMode() {
    editedProgramNumber = currentSetlist[selectedIndex].number;
    isEditMode = true;
    
    auto view = diContainer->getEditSetlistView();
    view->setEditMode(true);
    view->setEditedProgramIndex(selectedIndex);
    view->setEditedProgramNumber(editedProgramNumber);
    
    const char* displayName = getProgramDisplayName(editedProgramNumber);
    view->setEditedProgramName(displayName);
}

// Utility methods
const char* EditSetlistState::getProgramDisplayName(int programNumber) {
    auto programsBank = diContainer->getProgramsBank();
    const char* name = programsBank->getProgramName(programNumber);
    
    if (name) {
        return name;
    }
    
    static char tempName[17];
    snprintf(tempName, 17, "Program %d", programNumber);
    return tempName;
}

void EditSetlistState::updateProgramInSetlist(int index, int programNumber) {
    currentSetlist[index].number = programNumber;
    
    const char* name = getProgramDisplayName(programNumber);
    strncpy(currentSetlist[index].name, name, 16);
    currentSetlist[index].name[16] = '\0';
}

void EditSetlistState::updateViewAfterEdit() {
    auto view = diContainer->getEditSetlistView();
    view->showSetlist(currentSetlist);
    view->setSelectedItemIndex(selectedIndex);
    view->setEditMode(false);
}
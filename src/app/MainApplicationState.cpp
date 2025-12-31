#include "MainApplicationState.h"

void MainApplicationState::enter() {
    // Empty implementation - no specific initialization needed
}

void MainApplicationState::update() {
    if (hasUserInput()) {
        userInput->update();
    }

    if (userButtonIsPressed()) {
        handleNextButtonPress();
    }

    if (rightButtonIsPressed()) {
        handleNextButtonPress();
    }
}

void MainApplicationState::exit() {
    // Empty implementation - no specific cleanup needed
}

bool MainApplicationState::userButtonIsPressed() {
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->userButtonIsPressed();
}

bool MainApplicationState::rightButtonIsPressed() {
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->rightButtonIsPressed();
}

void MainApplicationState::handleNextButtonPress() {
    selectNextProgram();
    sendSelectedProgram();
    updateProgramSelectionView();
}

void MainApplicationState::selectNextProgram() {
    if (false == hasProgramSelector()) {
        return;
    }

    programSelector->selectNextProgram();
}

void MainApplicationState::sendSelectedProgram() {
    if (false == hasMidiController()) {
        return;
    }

    int program = programSelector->getSelectedProgramNumber();
    midiController->sendProgramChange(program);
}

void MainApplicationState::updateProgramSelectionView() {
    if (false == hasProgramSelectionView()) {
        return;
    }

    int program = programSelector->getSelectedProgramNumber();
    programSelectionView->setSelectedProgramNumber(program);
    
    if (hasProgramsBank()) {
        const char* programName = programsBank->getProgramName(program);
        programSelectionView->displayProgramName(programName);
    }
}

bool MainApplicationState::hasProgramSelector() {
    return programSelector != nullptr;
}

bool MainApplicationState::hasUserInput() {
    return userInput != nullptr;
}

bool MainApplicationState::hasMidiController() {
    return midiController != nullptr;
}

bool MainApplicationState::hasProgramSelectionView() {
    return programSelectionView != nullptr;
}

bool MainApplicationState::hasProgramsBank() {
    return programsBank != nullptr;
}
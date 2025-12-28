#include "MainApplicationState.h"

MainApplicationState::MainApplicationState(UserInputInterface* userInput, 
                                          ProgramSelectorInterface* programSelector,
                                          MidiControllerInterface* midiController,
                                          ProgramSelectionViewInterface* programSelectionView)
    : userInput(userInput)
    , programSelector(programSelector)
    , midiController(midiController)
    , programSelectionView(programSelectionView) {
}

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
    if (false == hasProgramSelector()) {
        return;
    }

    programSelector->selectNextProgram();

    if (false == hasMidiController()) {
        return;
    }

    int program = programSelector->getSelectedProgramNumber();
    midiController->sendProgramChange(program);

    // Update view with selected program number
    if (hasProgramSelectionView()) {
        programSelectionView->setSelectedProgramNumber(program);
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
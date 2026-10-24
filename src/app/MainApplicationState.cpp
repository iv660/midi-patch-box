#include "MainApplicationState.h"

void MainApplicationState::enter() {
    sendSelectedProgram();
    updateProgramSelectionView();
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

    bool clockwise = encoderRotatedClockwise();
    bool counterClockwise = encoderRotatedCounterClockwise();
    
    if (clockwise || counterClockwise) {
        // Handle rotation directly here while we have the flags
        if (clockwise) {
            selectNextProgram();
        } else if (counterClockwise) {
            selectPreviousProgram();
        }
        
        // Note: Only update view, do NOT send MIDI for encoder rotation
        updateProgramSelectionView();
    }

    if (encoderButtonLongPressed()) {
        handleEncoderButtonLongPress();
    } else if (encoderButtonPressed()) {
        handleEncoderButtonPress();
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

bool MainApplicationState::encoderRotatedClockwise() {
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->encoderRotatedClockwise();
}

bool MainApplicationState::encoderRotatedCounterClockwise() {
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->encoderRotatedCounterClockwise();
}

bool MainApplicationState::encoderButtonPressed() {
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->encoderButtonPressed();
}

bool MainApplicationState::encoderButtonLongPressed() {
    if (false == hasUserInput()) {
        return false;
    }

    return userInput->encoderButtonLongPressed();
}

void MainApplicationState::handleNextButtonPress() {
    selectNextProgram();
    sendSelectedProgram();
    updateProgramSelectionView();
}

void MainApplicationState::handleEncoderRotation() {
    // Note: Don't call encoder methods again here - flags were already consumed in update()
    // This method is called with the knowledge that rotation was detected
    // Note: Only update view, do NOT send MIDI for encoder rotation
    updateProgramSelectionView();
}

void MainApplicationState::handleEncoderButtonPress() {
    sendSelectedProgram();
    updateProgramSelectionView();
}

void MainApplicationState::handleEncoderButtonLongPress() {
    changeToConfigMenuState();
}

void MainApplicationState::selectNextProgram() {
    if (false == hasProgramSelector()) {
        return;
    }

    programSelector->selectNextProgram();
}

void MainApplicationState::selectPreviousProgram() {
    if (false == hasProgramSelector()) {
        return;
    }

    programSelector->selectPreviousProgram();
}

void MainApplicationState::sendSelectedProgram() {
    if (false == hasMidiController()) {
        return;
    }

    int program = programSelector->getSelectedProgramNumber();
    midiController->sendProgramChange(program);
    lastSentProgram = program;
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
    
    // Highlight program only if it matches the last sent program
    if (lastSentProgram != -1 && program == lastSentProgram) {
        programSelectionView->highlightProgram();
    } else {
        programSelectionView->clearHighlight();
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

bool MainApplicationState::hasStateFactory() {
    return stateFactory != nullptr;
}

bool MainApplicationState::hasStateMachine() {
    return stateMachine != nullptr;
}

void MainApplicationState::changeToConfigMenuState() {
    if (hasStateFactory() && hasStateMachine()) {
        StateInterface* configMenuState = stateFactory->createConfigMenuState();
        stateMachine->changeState(configMenuState);
    }
}
#include "SetlistMenuState.h"

void SetlistMenuState::enter() {
    if (false == hasSetlistMenuController()) {
        return;
    }

    char title[] = "Setlist";
    getSetlistMenuController()->setTitle(title);
    getSetlistMenuController()->addMenuItem("Back", [this]() {
        changeToMainApplicationState();
    });
}

void SetlistMenuState::update() {
    if (false == hasUserInput()) {
        return;
    }

    updateUserInput();

    if (encoderRotatedCounterClockwise()) {
        getSetlistMenuController()->selectPrevious();
        return;
    }

    if (encoderButtonPressed()) {
        performMenuItemAction();
        return;
    }
}

void SetlistMenuState::exit() {
    // Cleanup if needed
}

bool SetlistMenuState::hasSetlistMenuController() {
    return getSetlistMenuController() != nullptr;
}

bool SetlistMenuState::hasUserInput() {
    return getUserInput() != nullptr;
}

void SetlistMenuState::updateUserInput() {
    if (getUserInput()) {
        getUserInput()->update();
    }
}

bool SetlistMenuState::encoderRotatedCounterClockwise() {
    if (false == hasUserInput()) {
        return false;
    }
    return getUserInput()->encoderRotatedCounterClockwise();
}

bool SetlistMenuState::encoderButtonPressed() {
    if (false == hasUserInput()) {
        return false;
    }
    return getUserInput()->encoderButtonPressed();
}

void SetlistMenuState::performMenuItemAction() {
    getSetlistMenuController()->executeSelectedAction();
}

void SetlistMenuState::changeToMainApplicationState() {
    if (getStateFactory() && getStateMachine()) {
        StateInterface* mainState = getStateFactory()->createMainApplicationState();
        getStateMachine()->changeState(mainState);
    }
}

#include "ConfigMenuState.h"

void ConfigMenuState::enter() {
    if (getMenuController() == nullptr) {
        return;
    }

    initializeView();
}

void ConfigMenuState::update() {
    if (false == hasUserInput()) {
        return;
    }

    updateUserInput();

    if (encoderRotatedClockwise()) {
        selectNextMenuItem();
        return;
    }

    if (encoderRotatedCounterClockwise()) {
        selectPreviousMenuItem();
        return;
    }

    if (encoderButtonPressed()) {
        performMenuItemAction();
        return;
    }
}

void ConfigMenuState::performMenuItemAction() {
    if (getMenuController()) {
        getMenuController()->executeSelectedAction();
    }
}

void ConfigMenuState::exit() {
    // Cleanup if needed
}

bool ConfigMenuState::hasUserInput() {
    return getUserInput() != nullptr;
}

void ConfigMenuState::initializeView() {
    MenuControllerInterface* menuController = getMenuController();
    if (menuController) {
        menuController->resetMenuItems();
        menuController->setTitle(const_cast<char*>("Configuration"));
        menuController->addMenuItem(const_cast<char*>("Edit Setlist"), [this]() { changeToSetlistMenuState(); });
        menuController->addMenuItem(const_cast<char*>("Back"), [this]() { changeToMainApplicationState(); });
    }
}

void ConfigMenuState::updateUserInput() {
    if (getUserInput()) {
        getUserInput()->update();
    }
}

bool ConfigMenuState::encoderRotatedClockwise() {
    if (false == hasUserInput()) {
        return false;
    }
    return getUserInput()->encoderRotatedClockwise();
}

bool ConfigMenuState::encoderRotatedCounterClockwise() {
    if (false == hasUserInput()) {
        return false;
    }
    return getUserInput()->encoderRotatedCounterClockwise();
}

bool ConfigMenuState::encoderButtonPressed() {
    if (false == hasUserInput()) {
        return false;
    }
    return getUserInput()->encoderButtonPressed();
}

void ConfigMenuState::selectNextMenuItem() {
    if (getMenuController()) {
        getMenuController()->selectNext();
    }
}

void ConfigMenuState::selectPreviousMenuItem() {
    if (getMenuController()) {
        getMenuController()->selectPrevious();
    }
}

void ConfigMenuState::changeToSetlistMenuState() {
    if (getStateFactory() && getStateMachine()) {
        StateInterface* setlistMenuState = getStateFactory()->createSetlistMenuState();
        getStateMachine()->changeState(setlistMenuState);
    }
}

void ConfigMenuState::changeToMainApplicationState() {
    if (getStateFactory() && getStateMachine()) {
        StateInterface* mainState = getStateFactory()->createMainApplicationState();
        getStateMachine()->changeState(mainState);
    }
}

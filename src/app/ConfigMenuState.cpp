#include "ConfigMenuState.h"

void ConfigMenuState::enter() {
    if (false == hasConfigMenuView()) {
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
    if (selectedMenuItem == MENU_ITEM_EDIT_SETLIST) {
        changeToEditSetlistState();
        return;
    }

    if (selectedMenuItem == MENU_ITEM_BACK) {
        changeToMainApplicationState();
        return;
    }
}

void ConfigMenuState::exit() {
    // Cleanup if needed
}

bool ConfigMenuState::hasConfigMenuView() {
    return configMenuView != nullptr;
}

bool ConfigMenuState::hasUserInput() {
    return userInput != nullptr;
}

void ConfigMenuState::initializeView() {
    if (configMenuView) {
        configMenuView->showMenu();
        configMenuView->setSelectedItem(0);
        configMenuView->displayMenuItem(0, "Edit Setlist");
        configMenuView->displayMenuItem(1, "Back");
    }
}

void ConfigMenuState::updateUserInput() {
    userInput->update();
}

bool ConfigMenuState::encoderRotatedClockwise() {
    if (false == hasUserInput()) {
        return false;
    }
    return userInput->encoderRotatedClockwise();
}

bool ConfigMenuState::encoderRotatedCounterClockwise() {
    if (false == hasUserInput()) {
        return false;
    }
    return userInput->encoderRotatedCounterClockwise();
}

bool ConfigMenuState::encoderButtonPressed() {
    if (false == hasUserInput()) {
        return false;
    }
    return userInput->encoderButtonPressed();
}

void ConfigMenuState::handleEncoderRotation() {
    if (encoderRotatedClockwise()) {
        selectNextMenuItem();
        return;
    }
    
    if (encoderRotatedCounterClockwise()) {
        selectPreviousMenuItem();
        return;
    }
}

void ConfigMenuState::handleEncoderButtonPress() {
    if (encoderButtonPressed()) {
        performMenuItemAction();
    }
}

void ConfigMenuState::selectNextMenuItem() {
    selectedMenuItem = (selectedMenuItem + 1) % TOTAL_MENU_ITEMS;
    updateMenuView();
}

void ConfigMenuState::selectPreviousMenuItem() {
    selectedMenuItem = (selectedMenuItem - 1 + TOTAL_MENU_ITEMS) % TOTAL_MENU_ITEMS;
    updateMenuView();
}

void ConfigMenuState::updateMenuView() {
    if (configMenuView) {
        configMenuView->setSelectedItem(selectedMenuItem);
    }
}

void ConfigMenuState::changeToEditSetlistState() {
    if (stateFactory && stateMachine) {
        StateInterface* editSetlistState = stateFactory->createEditSetlistState();
        stateMachine->changeState(editSetlistState);
    }
}

void ConfigMenuState::changeToMainApplicationState() {
    if (stateFactory && stateMachine) {
        StateInterface* mainState = stateFactory->createMainApplicationState();
        stateMachine->changeState(mainState);
    }
}

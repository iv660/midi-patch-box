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
        changeToSetlistMenuState();
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
    return getConfigMenuView() != nullptr;
}

bool ConfigMenuState::hasUserInput() {
    return getUserInput() != nullptr;
}

void ConfigMenuState::initializeView() {
    if (getConfigMenuView()) {
        getConfigMenuView()->showMenu();
        getConfigMenuView()->setSelectedItem(0);
        getConfigMenuView()->displayMenuItem(0, "Edit Setlist");
        getConfigMenuView()->displayMenuItem(1, "Back");
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
    if (getConfigMenuView()) {
        getConfigMenuView()->setSelectedItem(selectedMenuItem);
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

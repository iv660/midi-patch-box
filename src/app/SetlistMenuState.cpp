#include "SetlistMenuState.h"
#include <cstdio>

void SetlistMenuState::enter() {
    if (false == hasSetlistMenuController()) {
        return;
    }

    resetMenuItems();
    initializeMenuTitle();
    addProgramMenuItems();
    addBackMenuItem();
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
    if (false == hasUserInput()) {
        return;
    }

    getUserInput()->update();
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
    if (!getStateFactory()) {
        return;
    }

    if (!getStateMachine()) {
        return;
    }

    StateInterface* mainState = 
        getStateFactory()->createMainApplicationState();
    getStateMachine()->changeState(mainState);
}

void SetlistMenuState::resetMenuItems() {
    getSetlistMenuController()->resetMenuItems();
}

void SetlistMenuState::initializeMenuTitle() {
    char title[] = "Edit setlist";
    getSetlistMenuController()->setTitle(title);
}

void SetlistMenuState::addBackMenuItem() {
    char backLabel[] = "Back";
    getSetlistMenuController()->addMenuItem(backLabel, [this]() {
        changeToMainApplicationState();
    });
}

void SetlistMenuState::addProgramMenuItems() {
    if (context == nullptr || context->programs == nullptr) {
        return;
    }

    for (int index = 0; index < context->programsCount; index++) {
        int programNumber = context->programs[index];
        const char* caption = makeProgramCaption(programNumber);
        getSetlistMenuController()->addMenuItem(const_cast<char*>(caption), nullptr);
    }
}

const char* SetlistMenuState::makeProgramCaption(int programNumber)
{
    static char caption[16];

    ProgramsBankInterface* programsBank = getProgramsBank();
    const char* programName = programsBank ? programsBank->getProgramName(programNumber) : "";

    snprintf(caption, sizeof(caption), "%d %s", programNumber, programName);
    caption[15] = '\0';
    
    return caption;
}

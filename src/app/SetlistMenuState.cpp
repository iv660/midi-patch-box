#include "SetlistMenuState.h"
#include "SetlistMenuViewDecorator.h"
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

    if (isInEditMode()) {
        handleEditModeActions();
    } else {
        handleNavigationModeActions();
    }
}

bool SetlistMenuState::isInEditMode() const {
    return editModeEnabled;
}

void SetlistMenuState::handleEditModeActions() {
    if (encoderRotatedClockwise()) {
        selectNextProgramOption();
        return;
    }

    if (encoderRotatedCounterClockwise()) {
        selectPreviousProgramOption();
        return;
    }

    if (encoderButtonPressed()) {
        editModeEnabled = false;
        changeToMainApplicationState();
        return;
    }
}

void SetlistMenuState::selectNextProgramOption() {
    if (!context || !context->programs) {
        return;
    }

    int nextIndex = currentEditProgramIndex + 1;
    if (nextIndex >= context->programsCount) {
        nextIndex = 0;
    }

    switchToProgramOption(nextIndex);
}

void SetlistMenuState::selectPreviousProgramOption() {
    if (!context || !context->programs) {
        return;
    }

    int prevIndex = currentEditProgramIndex - 1;
    if (prevIndex < 0) {
        prevIndex = context->programsCount - 1;
    }

    switchToProgramOption(prevIndex);
}

void SetlistMenuState::switchToProgramOption(int newProgramIndex) {
    currentEditProgramIndex = newProgramIndex;
    redrawCurrentProgramOption();
}

void SetlistMenuState::redrawCurrentProgramOption() {
    if (!getMenuView()) {
        return;
    }

    if (!context || !context->programs) {
        return;
    }

    int programNumber = context->programs[currentEditProgramIndex];
    const char* caption = makeProgramCaption(programNumber);

    SetlistMenuViewDecorator* view = static_cast<SetlistMenuViewDecorator*>(getMenuView());
    view->replaceLastHighlightedItem(const_cast<char*>(caption));
}

void SetlistMenuState::handleNavigationModeActions() {
    if (encoderRotatedClockwise()) {
        getSetlistMenuController()->selectNext();
        return;
    }

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

bool SetlistMenuState::encoderRotatedClockwise() {
    if (false == hasUserInput()) {
        return false;
    }
    return getUserInput()->encoderRotatedClockwise();
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
        getSetlistMenuController()->addMenuItem(const_cast<char*>(caption), [this, index]() {
            switchToEditMode(index);
        });
    }
}

void SetlistMenuState::switchToEditMode(int programIndex) {
    if (!context || !context->programs) {
        return;
    }

    editModeEnabled = true;
    currentEditProgramIndex = programIndex;
    redrawCurrentProgramOption();
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

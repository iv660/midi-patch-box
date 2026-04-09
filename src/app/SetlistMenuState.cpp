#include "SetlistMenuState.h"

void SetlistMenuState::enter() {
    if (false == hasSetlistMenuController()) {
        return;
    }

    char title[] = "Setlist";
    getSetlistMenuController()->setTitle(title);
}

void SetlistMenuState::update() {
    // Not implemented yet
}

void SetlistMenuState::exit() {
    // Cleanup if needed
}

bool SetlistMenuState::hasSetlistMenuController() {
    return getSetlistMenuController() != nullptr;
}

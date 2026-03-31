#include "SetlistMenuState.h"

void SetlistMenuState::enter() {
    if (false == hasMenuController()) {
        return;
    }

    getMenuController()->setTitle("Setlist");
}

void SetlistMenuState::update() {
    // Not implemented yet
}

void SetlistMenuState::exit() {
    // Cleanup if needed
}

bool SetlistMenuState::hasMenuController() {
    return getMenuController() != nullptr;
}

#include "MenuController.h"

void MenuController::setTitle(char* title) {
    if (false == hasView()) {
        return;
    }

    getView()->setTitle(title);
}

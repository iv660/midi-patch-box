#include "MenuController.h"

void MenuController::setView(MenuLayoutViewInterface* view) {
    this->view = view;
}

void MenuController::setTitle(char* title) {
    if (view) {
        view->setTitle(title);
    }
}

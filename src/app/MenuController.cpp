#include "MenuController.h"
#include <cstring>

MenuControllerInterface* MenuController::setTitle(char* title) {
    if (false == hasView()) {
        return this;
    }

    getView()->setTitle(title);
    return this;
}

MenuControllerInterface* MenuController::addMenuItem(char* caption, std::function<void()> action) {
    if (itemCount >= 10 || caption == nullptr) {
        return this;
    }
    
    itemCount++;

    int newItemIndex = itemCount - 1;
    
    strncpy(menuItems[newItemIndex].caption, caption, 16);
    menuItems[newItemIndex].caption[15] = '\0';
    menuItems[newItemIndex].action = action;
    
    updateView();

    return this;
}

MenuControllerInterface* MenuController::selectNext() {
    if (itemCount == 0) {
        return this;
    }
    
    selectedIndex = (selectedIndex + 1) % itemCount;
    
    updateView();
    return this;
}

MenuControllerInterface* MenuController::selectPrevious() {
    if (itemCount == 0) {
        return this;
    }
    
    selectedIndex = (selectedIndex - 1 + itemCount) % itemCount;
    
    updateView();
    return this;
}

void MenuController::executeSelectedAction() {
    if (selectedIndex >= 0 && selectedIndex < itemCount) {
        if (menuItems[selectedIndex].action) {
            menuItems[selectedIndex].action();
        }
    }
}

void MenuController::updateView() {
    if (!hasView()) {
        return;
    }
    
    getView()->resetItems();
    
    for (int i = 0; i < itemCount; i++) {
        bool highlighted = (i == selectedIndex);
        getView()->addItem(menuItems[i].caption, highlighted);
    }
}

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
    if (!hasItems()) {
        return this;
    }

    if (lastItemIsSelected()) {
        moveViewportToTop();
        moveSelectionToTop();
        updateView();
        return this;
    }

    if (selectionIsAtBottomOfViewport()) {
        moveViewportDown();
        moveSelectionDown();
        updateView();
        return this;
    }

    moveSelectionDown();
    updateView();
    return this;
}

MenuControllerInterface* MenuController::selectPrevious() {
    if (!hasItems()) {
        return this;
    }

    if (selectedIndex == 0) {
        moveViewportToBottom();
        selectedIndex = itemCount - 1;
        updateView();
        return this;
    }

    if (selectionIsAtTopOfViewport()) {
        moveViewportUp();
        moveSelectionUp();
        updateView();
        return this;
    }

    moveSelectionUp();
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

    unsigned int viewportSize = getViewportSize();
    
    for (unsigned int viewportIndex = 0; viewportIndex < viewportSize; viewportIndex++) {
        int menuIndex = scrollOffset + viewportIndex;
        if (menuIndex >= itemCount) break;
        
        bool isHighlighted = (menuIndex == selectedIndex);
        MenuItem menuItem = getMenuItem(menuIndex);
        getView()->addItem(menuItem.caption, isHighlighted);
    }
}

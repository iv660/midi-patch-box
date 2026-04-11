#pragma once

#include "MenuLayoutViewInterface.h"
#include "MenuControllerInterface.h"
#include "DiContainerInterface.h"
#include <functional>

struct MenuItem {
    char caption[16];
    std::function<void()> action;
};

class MenuController: public MenuControllerInterface {
public:
    MenuController() = default;
    
    explicit MenuController(DiContainerInterface* container) : diContainer(container) {
    }
    
    MenuControllerInterface* setTitle(char* title) override;
    MenuControllerInterface* addMenuItem(char* caption, std::function<void()> action) override;
    MenuControllerInterface* selectNext() override;
    MenuControllerInterface* selectPrevious() override;
    void executeSelectedAction() override;

private:
    DiContainerInterface* diContainer = nullptr;
    MenuItem menuItems[10];
    int itemCount = 0;
    int selectedIndex = 0;
    int scrollOffset = 0;
    
    MenuLayoutViewInterface* getView() const {
        return diContainer ? diContainer->getSetlistMenuLayoutView() : nullptr;
    }
    
    bool hasView() const {
        return getView() != nullptr;
    }
    
    bool hasItems() const {
        return itemCount > 0;
    }
    
    unsigned int getViewportSize() const {
        return hasView() ? getView()->getMaxItems() : 0;
    }
    
    bool lastItemIsSelected() const {
        return selectedIndex == itemCount - 1;
    }
    
    bool selectionIsAtBottomOfViewport() const {
        return selectedIndex == scrollOffset + (int)getViewportSize() - 1;
    }
    
    bool selectionIsAtTopOfViewport() const {
        return selectedIndex == scrollOffset;
    }
    
    void moveViewportToTop() {
        scrollOffset = 0;
    }
    
    void moveSelectionToTop() {
        selectedIndex = 0;
    }
    
    void moveViewportDown() {
        scrollOffset++;
    }
    
    void moveViewportUp() {
        scrollOffset--;
    }
    
    void moveSelectionDown() {
        selectedIndex++;
    }
    
    void moveSelectionUp() {
        selectedIndex--;
    }
    
    void moveViewportToBottom() {
        scrollOffset = itemCount - (int)getViewportSize();
        if (scrollOffset < 0) scrollOffset = 0;
    }
    
    MenuItem getMenuItem(int index) {
        return menuItems[index];
    }
    
    void updateView();
};

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
    
    MenuLayoutViewInterface* getView() const {
        return diContainer ? diContainer->getSetlistMenuLayoutView() : nullptr;
    }
    
    bool hasView() const {
        return getView() != nullptr;
    }
    
    void updateView();
};

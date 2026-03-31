#pragma once

#include "MenuLayoutViewInterface.h"
#include "MenuControllerInterface.h"

class MenuController: public MenuControllerInterface {
public:
    void setView(MenuLayoutViewInterface* view) override;
    void setTitle(char* title) override;

private:
    MenuLayoutViewInterface* view;
};

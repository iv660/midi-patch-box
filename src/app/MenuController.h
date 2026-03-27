#pragma once

#include "MenuLayoutViewInterface.h"

class MenuController {
public:
    void setView(MenuLayoutViewInterface* view);
    void setTitle(char* title);

private:
    MenuLayoutViewInterface* view;
};

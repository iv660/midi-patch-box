#pragma once

#include "MenuLayoutViewInterface.h"

class MenuControllerInterface {
public:
    virtual void setView(MenuLayoutViewInterface* view) = 0;
    virtual void setTitle(char* title) = 0;
};

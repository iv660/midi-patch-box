#pragma once

#include "MenuLayoutViewInterface.h"
#include <functional>

class MenuControllerInterface {
public:
    virtual MenuControllerInterface* setTitle(char* title) = 0;
    virtual MenuControllerInterface* addMenuItem(char* caption, std::function<void()> action) = 0;
    virtual MenuControllerInterface* selectNext() = 0;
    virtual MenuControllerInterface* selectPrevious() = 0;
    virtual void executeSelectedAction() = 0;
    virtual ~MenuControllerInterface() = default;
};

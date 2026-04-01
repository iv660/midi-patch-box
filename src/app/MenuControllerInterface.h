#pragma once

#include "MenuLayoutViewInterface.h"

class MenuControllerInterface {
public:
    virtual void setTitle(char* title) = 0;
    virtual ~MenuControllerInterface() = default;
};

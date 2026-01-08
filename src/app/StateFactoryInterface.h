#pragma once
#include "StateInterface.h"

class StateFactoryInterface {
public:
    virtual ~StateFactoryInterface() = default;
    virtual StateInterface* createMainApplicationState() = 0;
    virtual StateInterface* createConfigMenuState() = 0;
    virtual StateInterface* createEditSetlistState() = 0;
};
#pragma once
#include "StateInterface.h"

class StateFactoryInterface {
public:
    virtual ~StateFactoryInterface() = default;
    virtual StateInterface* createMainApplicationState() = 0;
};
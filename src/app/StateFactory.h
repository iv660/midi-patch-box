#pragma once
#include "StateFactoryInterface.h"

class StateFactory : public StateFactoryInterface {
public:
    virtual ~StateFactory() = default;
    virtual StateInterface* createMainApplicationState() = 0;
};
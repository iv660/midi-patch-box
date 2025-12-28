#pragma once
#include "StateInterface.h"

class StateMachineInterface {
public:
    virtual ~StateMachineInterface() = default;
    virtual void changeState(StateInterface* newState) = 0;
    virtual void update() = 0;
};
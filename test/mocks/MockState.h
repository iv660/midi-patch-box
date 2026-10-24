#pragma once
#include "app/StateInterface.h"
#include "app/StateMachineInterface.h"

class MockState : public StateInterface {
public:
    void enter() override {}
    void update() override {}
    void exit() override {}
    StateInterface* setStateMachine(StateMachineInterface* stateMachine) override { return this; }
};

#pragma once
#include "app/StateMachineInterface.h"

class MockStateMachine : public StateMachineInterface {
private:
    bool changeStateCalled = false;
    StateInterface* lastChangedState = nullptr;

public:
    void changeState(StateInterface* newState) override {
        changeStateCalled = true;
        lastChangedState = newState;
    }

    void update() override {}

    bool changeStateWasCalled() const { return changeStateCalled; }
    StateInterface* getLastChangedState() const { return lastChangedState; }
};

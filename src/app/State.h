#pragma once
#include "StateInterface.h"

class StateMachineInterface; // Forward declaration

// Abstract base class for states
class State : public StateInterface {
protected:
    StateMachineInterface* stateMachine = nullptr;

public:
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
    virtual ~State() = default;

    // Method for injecting state machine reference
    void setStateMachine(StateMachineInterface* stateMachine) override {
        this->stateMachine = stateMachine;
    }
};
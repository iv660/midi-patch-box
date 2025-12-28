#pragma once

class StateMachineInterface; // Forward declaration

class StateInterface {
public:
    virtual ~StateInterface() = default;
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
    virtual void setStateMachine(StateMachineInterface* stateMachine) = 0;
};
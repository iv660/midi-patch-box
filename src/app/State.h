#pragma once

class StateMachine; // Forward declaration

// Abstract base class for states
class State {
protected:
    StateMachine* stateMachine = nullptr;

public:
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
    virtual ~State() = default;

    // Method for injecting state machine reference
    void setStateMachine(StateMachine* stateMachine) {
        this->stateMachine = stateMachine;
    }
};
#pragma once
#include "State.h"

class StateMachine {
private:
    State* currentState = nullptr;

public:
    void changeState(State* newState) {
        if (currentState) {
            currentState->exit();
            delete currentState;
        }
        
        currentState = newState;
        // Inject state machine reference into new state
        if (currentState) {
            currentState->setStateMachine(this);
            currentState->enter();
        }
    }

    void update() {
        if (currentState) {
            currentState->update();
        }
    }

    // Method for changing state from within a state
    template<typename NewStateType>
    void transitionTo() {
        changeState(new NewStateType());
    }

    ~StateMachine() {
        if (currentState) {
            currentState->exit();
            delete currentState;
        }
    }
};
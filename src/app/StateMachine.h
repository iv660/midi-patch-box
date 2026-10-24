#pragma once
#include "State.h"
#include "StateMachineInterface.h"

class StateMachine : public StateMachineInterface {
private:
    StateInterface* currentState = nullptr;

public:
    void changeState(StateInterface* newState) override {
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

    void update() override {
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
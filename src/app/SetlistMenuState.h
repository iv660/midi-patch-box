#pragma once
#include "State.h"
#include "MenuControllerInterface.h"
#include "DiContainerInterface.h"
#include "UserInputInterface.h"
#include "StateFactoryInterface.h"
#include "StateMachineInterface.h"

class SetlistMenuState : public State {
private:
    MenuControllerInterface* getSetlistMenuController() const {
        return diContainer ? diContainer->getSetlistMenuController() : nullptr;
    }
    UserInputInterface* getUserInput() const {
        return diContainer ? diContainer->getUserInput() : nullptr;
    }
    StateFactoryInterface* getStateFactory() const {
        return diContainer ? diContainer->getStateFactory() : nullptr;
    }
    StateMachineInterface* getStateMachine() const {
        return diContainer ? diContainer->getStateMachine() : nullptr;
    }

    bool hasSetlistMenuController();
    bool hasUserInput();
    void updateUserInput();
    bool encoderRotatedCounterClockwise();
    bool encoderButtonPressed();
    void performMenuItemAction();
    void changeToMainApplicationState();
    void resetMenuItems();
    void initializeMenuTitle();
    void addBackMenuItem();

public:
    SetlistMenuState() = default;
    
    explicit SetlistMenuState(DiContainerInterface* container) : State(container) {
    }

    void enter() override;
    void update() override;
    void exit() override;
};

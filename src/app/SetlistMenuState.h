#pragma once
#include "State.h"
#include "MenuControllerInterface.h"
#include "DiContainerInterface.h"

class SetlistMenuState : public State {
private:
    MenuControllerInterface* getSetlistMenuController() const {
        return diContainer ? diContainer->getSetlistMenuController() : nullptr;
    }

    bool hasSetlistMenuController();

public:
    SetlistMenuState() = default;
    
    explicit SetlistMenuState(DiContainerInterface* container) : State(container) {
    }

    void enter() override;
    void update() override;
    void exit() override;
};

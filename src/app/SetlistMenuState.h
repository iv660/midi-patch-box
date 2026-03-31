#pragma once
#include "State.h"
#include "MenuControllerInterface.h"
#include "DiContainerInterface.h"

class SetlistMenuState : public State {
private:
    MenuControllerInterface* menuController = nullptr;

    MenuControllerInterface* getMenuController() const {
        return menuController ? menuController : (diContainer ? diContainer->getMenuController() : nullptr);
    }

    bool hasMenuController();

public:
    SetlistMenuState() = default;
    
    explicit SetlistMenuState(DiContainerInterface* container) : State(container) {
    }

    void enter() override;
    void update() override;
    void exit() override;
};

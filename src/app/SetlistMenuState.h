#pragma once
#include "State.h"
#include "MenuControllerInterface.h"
#include "DiContainerInterface.h"
#include "Context.h"
#include "UserInputInterface.h"
#include "StateFactoryInterface.h"
#include "StateMachineInterface.h"
#include "ProgramsBankInterface.h"

class SetlistMenuState : public State {
private:
    const Context* context = nullptr;

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

    ProgramsBankInterface* getProgramsBank() const {
        return diContainer ? diContainer->getProgramsBank() : nullptr;
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
    void addProgramMenuItems();
    const char* makeProgramCaption(int programNumber);
    void addBackMenuItem();

public:
    SetlistMenuState() = default;
    
    explicit SetlistMenuState(DiContainerInterface* container, const Context* context = nullptr)
        : State(container), context(context) {
    }

    void enter() override;
    void update() override;
    void exit() override;
};

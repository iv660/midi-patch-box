#pragma once
#include "State.h"
#include "UserInputInterface.h"
#include "ConfigMenuViewInterface.h"
#include "StateFactoryInterface.h"
#include "StateMachineInterface.h"

class ConfigMenuState : public State {
private:
    UserInputInterface* userInput = nullptr;
    ConfigMenuViewInterface* configMenuView = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    StateMachineInterface* stateMachine = nullptr;
    int selectedMenuItem = 0;
    
    const int MENU_ITEM_EDIT_SETLIST = 0;
    const int MENU_ITEM_BACK = 1;
    const int TOTAL_MENU_ITEMS = 2;

    bool hasConfigMenuView();
    bool hasUserInput();
    void initializeView();
    void updateUserInput();
    bool encoderRotatedClockwise();
    bool encoderRotatedCounterClockwise();
    bool encoderButtonPressed();
    void handleEncoderRotation();
    void handleEncoderButtonPress();
    void selectNextMenuItem();
    void selectPreviousMenuItem();
    void updateMenuView();
    void changeToEditSetlistState();
    void changeToMainApplicationState();
    void performMenuItemAction();

public:
    ConfigMenuState() = default;
    
    ConfigMenuState* setUserInput(UserInputInterface* userInput) {
        this->userInput = userInput;
        return this;
    }
    
    ConfigMenuState* setConfigMenuView(ConfigMenuViewInterface* view) {
        this->configMenuView = view;
        return this;
    }
    
    ConfigMenuState* setStateFactory(StateFactoryInterface* factory) {
        this->stateFactory = factory;
        return this;
    }
    
    ConfigMenuState* withStateMachine(StateMachineInterface* machine) {
        this->stateMachine = machine;
        return this;
    }

    void enter() override;
    void update() override;
    void exit() override;
};
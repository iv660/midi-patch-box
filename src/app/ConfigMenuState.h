#pragma once
#include "State.h"
#include "UserInputInterface.h"
#include "ConfigMenuViewInterface.h"
#include "StateFactoryInterface.h"
#include "StateMachineInterface.h"
#include "DiContainerInterface.h"

class ConfigMenuState : public State {
private:
    UserInputInterface* userInput = nullptr;
    ConfigMenuViewInterface* configMenuView = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    int selectedMenuItem = 0;
    
    const int MENU_ITEM_EDIT_SETLIST = 0;
    const int MENU_ITEM_BACK = 1;
    const int TOTAL_MENU_ITEMS = 2;

    // Private getters
    UserInputInterface* getUserInput() const {
        return userInput ? userInput : (diContainer ? diContainer->getUserInput() : nullptr);
    }
    ConfigMenuViewInterface* getConfigMenuView() const {
        return configMenuView ? configMenuView : (diContainer ? diContainer->getConfigMenuView() : nullptr);
    }
    StateFactoryInterface* getStateFactory() const {
        return stateFactory ? stateFactory : (diContainer ? diContainer->getStateFactory() : nullptr);
    }
    StateMachineInterface* getStateMachine() const {
        return stateMachine ? stateMachine : (diContainer ? diContainer->getStateMachine() : nullptr);
    }

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
    void changeToSetlistMenuState();
    void changeToMainApplicationState();
    void performMenuItemAction();

public:
    ConfigMenuState() = default;
    
    // Constructor with DiContainer for dependency injection
    explicit ConfigMenuState(DiContainerInterface* container) : State(container) {
        // Dependencies will be resolved lazily through getters
    }
    
    /**
     * @deprecated Use DI container instead
     */
    ConfigMenuState* setUserInput(UserInputInterface* userInput) {
        this->userInput = userInput;
        return this;
    }
    
    /**
     * @deprecated Use DI container instead
     */
    ConfigMenuState* setConfigMenuView(ConfigMenuViewInterface* view) {
        this->configMenuView = view;
        return this;
    }
    
    /**
     * @deprecated Use DI container instead
     */
    ConfigMenuState* setStateFactory(StateFactoryInterface* factory) {
        this->stateFactory = factory;
        return this;
    }

    void enter() override;
    void update() override;
    void exit() override;
};
#pragma once
#include "State.h"
#include "SplashScreenViewInterface.h"
#include "IoDriverInterface.h"
#include "StateFactoryInterface.h"
#include "DiContainerInterface.h"

class SplashScreenState : public State {
private:
    SplashScreenViewInterface* splashScreenView = nullptr;
    IoDriverInterface* ioDriver = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    unsigned long startTime = 0;

    const unsigned long splashScreenDuration = 2000;
    
    // Private getters
    SplashScreenViewInterface* getSplashScreenView() const {
        return splashScreenView ? splashScreenView : (diContainer ? diContainer->getSplashScreenView() : nullptr);
    }
    IoDriverInterface* getIoDriver() const {
        return ioDriver ? ioDriver : (diContainer ? diContainer->getIoDriver() : nullptr);
    }
    StateFactoryInterface* getStateFactory() const {
        return stateFactory ? stateFactory : (diContainer ? diContainer->getStateFactory() : nullptr);
    }

public:
    SplashScreenState() = default;
    
    // Constructor with DiContainer for dependency injection
    explicit SplashScreenState(DiContainerInterface* container) : State(container) {
        // Dependencies will be resolved lazily through getters
    }
    
    SplashScreenState* setSplashScreenView(SplashScreenViewInterface* view) {
        this->splashScreenView = view;
        return this;
    }
    
    SplashScreenState* setIoDriver(IoDriverInterface* driver) {
        this->ioDriver = driver;
        return this;
    }
    
    SplashScreenState* setStateFactory(StateFactoryInterface* factory) {
        this->stateFactory = factory;
        return this;
    }
    
    
    void enter() override;
    void update() override;
    void exit() override;
};
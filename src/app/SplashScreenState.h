#pragma once
#include "State.h"
#include "SplashScreenViewInterface.h"
#include "IoDriverInterface.h"
#include "StateFactoryInterface.h"

class SplashScreenState : public State {
private:
    SplashScreenViewInterface* splashScreenView = nullptr;
    IoDriverInterface* ioDriver = nullptr;
    StateFactoryInterface* stateFactory = nullptr;
    unsigned long startTime = 0;

public:
    SplashScreenState() = default;
    
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
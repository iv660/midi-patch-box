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
    SplashScreenState(SplashScreenViewInterface* splashScreenView, IoDriverInterface* ioDriver = nullptr, StateFactoryInterface* stateFactory = nullptr);
    
    void enter() override;
    void update() override;
    void exit() override;
};
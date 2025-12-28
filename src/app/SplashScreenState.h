#pragma once
#include "State.h"
#include "SplashScreenViewInterface.h"

class SplashScreenState : public State {
private:
    SplashScreenViewInterface* splashScreenView = nullptr;

public:
    SplashScreenState(SplashScreenViewInterface* splashScreenView);
    
    void enter() override;
    void update() override;
    void exit() override;
};
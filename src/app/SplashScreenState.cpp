#include "SplashScreenState.h"
#include "StateMachine.h"


void SplashScreenState::enter() {
    if (getSplashScreenView()) {
        getSplashScreenView()->showMessage();
    }
    if (getIoDriver()) {
        startTime = getIoDriver()->millis();
    }
}

void SplashScreenState::update() {
    if (getIoDriver() && stateMachine && getStateFactory()) {
        unsigned long currentTime = getIoDriver()->millis();
        if (currentTime - startTime >= splashScreenDuration) {
            StateInterface* mainState = getStateFactory()->createMainApplicationState();
            stateMachine->changeState(mainState);
        }
    }
}

void SplashScreenState::exit() {
    if (getSplashScreenView()) {
        getSplashScreenView()->hide();
    }
}
#include "SplashScreenState.h"
#include "StateMachine.h"


void SplashScreenState::enter() {
    if (splashScreenView) {
        splashScreenView->showMessage();
    }
    if (ioDriver) {
        startTime = ioDriver->millis();
    }
}

void SplashScreenState::update() {
    if (ioDriver && stateMachine && stateFactory) {
        unsigned long currentTime = ioDriver->millis();
        if (currentTime - startTime >= 1000) {
            StateInterface* mainState = stateFactory->createMainApplicationState();
            stateMachine->changeState(mainState);
        }
    }
}

void SplashScreenState::exit() {
    if (splashScreenView) {
        splashScreenView->hide();
    }
}
#include "SplashScreenState.h"

SplashScreenState::SplashScreenState(SplashScreenViewInterface* splashScreenView)
    : splashScreenView(splashScreenView) {
}

void SplashScreenState::enter() {
    if (splashScreenView) {
        splashScreenView->showMessage();
    }
}

void SplashScreenState::update() {
    // Empty implementation for now - timer logic will be added later
}

void SplashScreenState::exit() {
    if (splashScreenView) {
        splashScreenView->hide();
    }
}
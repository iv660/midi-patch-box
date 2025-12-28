#pragma once

class SplashScreenViewInterface {
public:
    virtual ~SplashScreenViewInterface() = default;
    virtual void showMessage() = 0;
    virtual void hide() = 0;
};
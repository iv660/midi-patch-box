#pragma once

#include <Arduino.h>

class UserInput {
private:
    static const uint8_t buttonPin;
    bool lastButtonState;
    bool buttonPressed;

public:
    UserInput();
    void update();
    bool usrButtonIsPressed();
};
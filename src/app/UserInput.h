#pragma once

#include <Arduino.h>
#include "UserInputInterface.h"

class UserInput: public UserInputInterface {
private:
    static const uint8_t buttonPin;
    bool lastButtonState;
    bool buttonPressed;

public:
    UserInput();
    void update();
    bool userButtonIsPressed();
    bool rightButtonIsPressed();
};
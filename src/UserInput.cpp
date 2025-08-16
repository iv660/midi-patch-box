#include "UserInput.h"

const uint8_t UserInput::buttonPin = 24;

UserInput::UserInput() : lastButtonState(HIGH), buttonPressed(false) {
    pinMode(buttonPin, INPUT_PULLUP);
}

void UserInput::update() {
    bool currentState = digitalRead(buttonPin);
    if (lastButtonState == HIGH && currentState == LOW) {
        buttonPressed = true;
    } else {
        buttonPressed = false;
    }
    lastButtonState = currentState;
}

bool UserInput::usrButtonIsPressed() {
    return buttonPressed;
}


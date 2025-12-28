#include "Button.h"

Button::Button(int buttonPin) 
    : ioDriver(nullptr), 
      lastButtonState(HIGH), 
      buttonPressed(false), 
      pressStartTime(0), 
      debounceThreshold(20),
      buttonPin(buttonPin) {
}

Button* Button::setIoDriver(IoDriverInterface* ioDriver) {
    this->ioDriver = ioDriver;
    if (this->ioDriver) {
        this->ioDriver->pinMode(buttonPin, IoDriverInterface::INPUT_PULLUP);
    }
    return this;
}

void Button::update() {
    if (!ioDriver) return;
    
    bool currentState = ioDriver->digitalRead(buttonPin);
    unsigned long currentTime = ioDriver->millis();
    
    // Detect button press and release cycle with debounce
    if (lastButtonState == HIGH && currentState == LOW) {
        // Button was just pressed - record start time
        pressStartTime = currentTime;
        buttonPressed = false; // Not yet a complete press
    } else if (lastButtonState == LOW && currentState == HIGH) {
        // Button was just released - check if press duration meets threshold
        unsigned long pressDuration = currentTime - pressStartTime;
        if (pressDuration >= debounceThreshold) {
            buttonPressed = true; // Valid press detected
        } else {
            buttonPressed = false; // Too short, ignore
        }
    } else {
        // Reset after one read
        buttonPressed = false;
    }
    
    lastButtonState = currentState;
}

bool Button::isPressed() {
    return buttonPressed;
}
#include "Button.h"

Button::Button(int buttonPin)
    : ioDriver(nullptr),
      lastButtonState(HIGH),
      buttonPressed(false),
      longPressed(false),
      longPressDetectionEnabled(false),
      pressStartTime(0),
      debounceThreshold(20),
      longPressThreshold(1000),
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
    if (false == hasIoDriver()) {
        return;
    }

    updateCurrentState();
    updateCurrentTime();

    if (buttonWasJustPressed()) {
        // Button was just pressed - record start time
        recordStartTime();
        recordLastState();
        return;
    }

    if (currentState == LOW && pressDurationMeetsLongPressThreshold() && !longPressed) {
        // Button is still held and long press timer just expired
        recordLongPressDetection();
        recordLastState();
        return;
    }

    if (buttonWasJustReleased() && pressDurationMeetsLongPressThreshold()) {
        // Button was just released - press duration is above long press threshold
        recordLongPressDetection();
        recordLastState();
        return;
    }

    if (buttonWasJustReleased() && pressDurationMeetsDebounceThreshold()) {
        // Button was just released - press duration is above debounce threshold
        recordShortPressDetection();
        recordLastState();
        return;
    }

    if (buttonWasJustReleased()) {
        // Button was just released but too short - ignore
        recordLastState();
        return;
    }

    // Button is not currently pressed - reset flags after one read
    if (buttonIsNotCurrentlyPressed()) {
        resetFlags();
    }

    recordLastState();
}

// Helper method implementations
bool Button::hasIoDriver() const {
    return ioDriver != nullptr;
}

void Button::updateCurrentState() {
    currentState = ioDriver->digitalRead(buttonPin);
}

void Button::updateCurrentTime() {
    currentTime = ioDriver->millis();
}

bool Button::buttonWasJustPressed() const {
    return lastButtonState == HIGH && currentState == LOW;
}

bool Button::buttonWasJustReleased() const {
    return lastButtonState == LOW && currentState == HIGH;
}

bool Button::pressDurationMeetsLongPressThreshold() const {
    unsigned long pressDuration = currentTime - pressStartTime;
    return longPressDetectionEnabled && pressDuration >= longPressThreshold;
}

bool Button::pressDurationMeetsDebounceThreshold() const {
    unsigned long pressDuration = currentTime - pressStartTime;
    return pressDuration >= debounceThreshold;
}

void Button::recordStartTime() {
    pressStartTime = currentTime;
    buttonPressed = false; // Not yet a complete press
    longPressed = false; // Reset long press flag
}

void Button::recordLastState() {
    lastButtonState = currentState;
}

void Button::recordLongPressDetection() {
    longPressed = true; // Long press detected
    buttonPressed = false; // Don't trigger short press
}

void Button::recordShortPressDetection() {
    buttonPressed = true; // Short press detected
    longPressed = false; // Don't trigger long press
}

bool Button::buttonIsNotCurrentlyPressed() const {
    return currentState == HIGH;
}

void Button::resetFlags() {
    buttonPressed = false;
    longPressed = false;
}

bool Button::isPressed() {
    return buttonPressed;
}

bool Button::isLongPressed() {
    return longPressed;
}

ButtonInterface* Button::enableLongPressDetection() {
    longPressDetectionEnabled = true;
    return this;
}
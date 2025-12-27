#pragma once

#include "app/IoDriverInterface.h"

class MockIoDriver : public IoDriverInterface {
public:
    int digitalRead(int pin) override {
        return pin == BUTTON_PIN ? pinState : LOW;
    }

    void delay(unsigned long ms) override {
        currentTime += ms;
    }

    unsigned long millis() override {
        return currentTime;
    }

    void setPinState(int pin, int state) {
        if (pin == BUTTON_PIN) {
            pinState = state;
        }
    }

    void resetTime() {
        currentTime = 0;
    }

    void pinMode(int pin, int mode) override {
        pinModeWasCalled = true;
        lastPinModePin = pin;
        lastPinModeMode = mode;
    }

    bool wasPinModeCalledWith(int pin, int mode) {
        return pinModeWasCalled &&
               lastPinModePin == pin &&
               lastPinModeMode == mode;
    }

private:
    int pinState = HIGH; // Emulate pull-up resistor
    const int BUTTON_PIN = 2;
    unsigned long currentTime = 0;
    
    bool pinModeWasCalled = false;
    int lastPinModePin = -1;
    int lastPinModeMode = -1;
    
    static const int HIGH = 1;
    static const int LOW = 0;
};
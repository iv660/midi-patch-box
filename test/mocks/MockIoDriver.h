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

private:
    int pinState = HIGH; // Emulate pull-up resistor
    const int BUTTON_PIN = 2;
    unsigned long currentTime = 0;
    
    static const int HIGH = 1;
    static const int LOW = 0;
};
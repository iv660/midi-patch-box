#pragma once

#include "app/IoDriverInterface.h"
#include <vector>
#include <utility>

class MockIoDriver : public IoDriverInterface {
public:
    int digitalRead(int pin) override {
        if (pin == BUTTON_PIN) return pinState;
        if (pin == 4) return encoderPinAState;
        if (pin == 5) return encoderPinBState;
        if (pin == 6) return encoderButtonState;
        return LOW;
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
        } else if (pin == 4) {
            encoderPinAState = state;
        } else if (pin == 5) {
            encoderPinBState = state;
        } else if (pin == 6) {
            encoderButtonState = state;
        }
    }

    void resetTime() {
        currentTime = 0;
    }

    void pinMode(int pin, int mode) override {
        pinModeWasCalled = true;
        lastPinModePin = pin;
        lastPinModeMode = mode;
        pinModeCalls.push_back(std::make_pair(pin, mode));
    }

    bool wasPinModeCalledWith(int pin, int mode) {
        for (const auto& call : pinModeCalls) {
            if (call.first == pin && call.second == mode) {
                return true;
            }
        }
        return false;
    }

    void clearPinModeCalls() {
        pinModeCalls.clear();
        pinModeWasCalled = false;
    }

private:
    int pinState = HIGH; // Emulate pull-up resistor
    int encoderPinAState = HIGH; // Encoder pin A state
    int encoderPinBState = HIGH; // Encoder pin B state
    int encoderButtonState = HIGH; // Encoder button state
    const int BUTTON_PIN = 2;
    unsigned long currentTime = 0;
    
    bool pinModeWasCalled = false;
    int lastPinModePin = -1;
    int lastPinModeMode = -1;
    std::vector<std::pair<int, int>> pinModeCalls; // Track all pinMode calls
    
    static const int HIGH = 1;
    static const int LOW = 0;
};
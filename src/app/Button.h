#pragma once

#include "IoDriverInterface.h"
#include "ButtonInterface.h"

class Button : public ButtonInterface {
public:
    Button(int buttonPin);
    virtual ~Button() = default;

    Button* setIoDriver(IoDriverInterface* ioDriver);
    void update();
    bool isPressed();

private:
    IoDriverInterface* ioDriver;
    bool lastButtonState;
    bool buttonPressed;
    unsigned long pressStartTime;
    const unsigned long debounceThreshold;
    const int buttonPin;
    
    static const int HIGH = 1;
    static const int LOW = 0;
};
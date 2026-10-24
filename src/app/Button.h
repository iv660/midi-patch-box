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
    bool isLongPressed();
    ButtonInterface* enableLongPressDetection();

private:
    IoDriverInterface* ioDriver;
    bool lastButtonState;
    bool buttonPressed;
    bool longPressed;
    bool longPressDetectionEnabled;
    unsigned long pressStartTime;
    unsigned long currentTime;
    bool currentState;
    const unsigned long debounceThreshold;
    const unsigned long longPressThreshold;
    const int buttonPin;
    
    static const int HIGH = 1;
    static const int LOW = 0;
    
    // Helper methods for clean code structure
    bool hasIoDriver() const;
    void updateCurrentState();
    void updateCurrentTime();
    bool buttonWasJustPressed() const;
    bool buttonWasJustReleased() const;
    bool pressDurationMeetsLongPressThreshold() const;
    bool pressDurationMeetsDebounceThreshold() const;
    void recordStartTime();
    void recordLastState();
    void recordLongPressDetection();
    void recordShortPressDetection();
    bool buttonIsNotCurrentlyPressed() const;
    void resetFlags();
};
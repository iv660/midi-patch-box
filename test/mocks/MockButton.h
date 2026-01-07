#pragma once

#include "app/ButtonInterface.h"

class MockButton : public ButtonInterface {
public:
    MockButton() : buttonPressed(false), longPressed(false), stateHasChanged(false) {}
    
    void update() override {
        // If state changed during this cycle, don't reset flags yet
        if (stateHasChanged) {
            stateHasChanged = false; // Reset the change flag
        } else {
            // No state change - reset button flags (like real Button when released)
            buttonPressed = false;
            longPressed = false;
        }
    }
    
    bool isPressed() override {
        return buttonPressed;
    }
    
    bool isLongPressed() override {
        return longPressed;
    }
    
    ButtonInterface* enableLongPressDetection() override {
        return this; // Mock implementation - just return this for fluent interface
    }
    
    // Mock-specific methods for test control
    void press() {
        buttonPressed = true;
        stateHasChanged = true;
    }
    
    void longPress() {
        longPressed = true;
        stateHasChanged = true;
    }

private:
    bool buttonPressed;
    bool longPressed;
    bool stateHasChanged;
};
#pragma once

#include "app/ButtonInterface.h"

class MockButton : public ButtonInterface {
public:
    MockButton() : buttonPressed(false) {}
    
    void update() override {
        // Mock implementation - no additional logic needed
    }
    
    bool isPressed() override {
        bool result = buttonPressed;
        buttonPressed = false; // Reset after reading (single-shot behavior)
        return result;
    }
    
    // Mock-specific method for test control
    void press() {
        buttonPressed = true;
    }

private:
    bool buttonPressed;
};
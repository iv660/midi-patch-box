#pragma once
#include "../../src/app/UserInputInterface.h"

class MockInput : public UserInputInterface {
private:
    bool encoderClockwiseState = false;
    bool encoderCounterClockwiseState = false;
    bool encoderButtonPressedState = false;
    bool encoderButtonLongPressedState = false;
    bool userButtonPressedState = false;
    bool rightButtonPressedState = false;

public:
    // Interface methods
    void update() override {
        // Mock implementation - no actual hardware polling needed
    }
    
    bool userButtonIsPressed() override {
        return userButtonPressedState;
    }
    
    bool rightButtonIsPressed() override {
        return rightButtonPressedState;
    }
    
    bool encoderRotatedClockwise() override {
        return encoderClockwiseState;
    }
    
    bool encoderRotatedCounterClockwise() override {
        return encoderCounterClockwiseState;
    }
    
    bool encoderButtonPressed() override {
        return encoderButtonPressedState;
    }
    
    bool encoderButtonLongPressed() override {
        return encoderButtonLongPressedState;
    }
    
    // Test helper methods
    void setEncoderClockwise(bool value) {
        encoderClockwiseState = value;
        encoderCounterClockwiseState = false; // Reset opposite direction
    }
    
    void setEncoderCounterClockwise(bool value) {
        encoderCounterClockwiseState = value;
        encoderClockwiseState = false; // Reset opposite direction
    }
    
    void setEncoderButtonPressed(bool value) {
        encoderButtonPressedState = value;
    }
    
    void setEncoderButtonLongPressed(bool value) {
        encoderButtonLongPressedState = value;
    }
    
    void setUserButtonPressed(bool value) {
        userButtonPressedState = value;
    }
    
    void setRightButtonPressed(bool value) {
        rightButtonPressedState = value;
    }
};
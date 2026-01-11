#pragma once
#include "../../src/app/UserInputInterface.h"

class MockInput : public UserInputInterface {
private:
    bool encoderClockwise = false;
    bool encoderCounterClockwise = false;
    bool encoderButtonPressed = false;
    bool encoderButtonLongPressed = false;

public:
    // Interface methods
    bool encoderRotatedClockwise() override {
        return encoderClockwise;
    }
    
    bool encoderRotatedCounterClockwise() override {
        return encoderCounterClockwise;
    }
    
    bool encoderButtonPressed() override {
        return encoderButtonPressed;
    }
    
    bool encoderButtonLongPressed() override {
        return encoderButtonLongPressed;
    }
    
    // Test helper methods
    void setEncoderClockwise(bool value) {
        encoderClockwise = value;
        encoderCounterClockwise = false; // Reset opposite direction
    }
    
    void setEncoderCounterClockwise(bool value) {
        encoderCounterClockwise = value;
        encoderClockwise = false; // Reset opposite direction
    }
    
    void setEncoderButtonPressed(bool value) {
        encoderButtonPressed = value;
    }
    
    void setEncoderButtonLongPressed(bool value) {
        encoderButtonLongPressed = value;
    }
};
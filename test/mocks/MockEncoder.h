#pragma once

#include "app/EncoderInterface.h"

class MockEncoder : public EncoderInterface {
public:
    MockEncoder() : clockwiseRotated(false), counterClockwiseRotated(false) {}
    
    void update() override {
        // Mock implementation - no additional logic needed
    }
    
    bool rotatedClockwise() override {
        bool result = clockwiseRotated;
        clockwiseRotated = false; // Reset after reading (single-shot behavior)
        return result;
    }
    
    bool rotatedCounterClockwise() override {
        bool result = counterClockwiseRotated;
        counterClockwiseRotated = false; // Reset after reading (single-shot behavior)
        return result;
    }
    
    // Mock-specific methods for test control
    void rotateClockwise() {
        clockwiseRotated = true;
    }
    
    void rotateCounterClockwise() {
        counterClockwiseRotated = true;
    }

private:
    bool clockwiseRotated;
    bool counterClockwiseRotated;
};
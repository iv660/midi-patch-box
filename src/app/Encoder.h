#pragma once

#include "EncoderInterface.h"

class IoDriverInterface; // Forward declaration

class Encoder : public EncoderInterface {
private:
    int pinA;
    int pinB;
    IoDriverInterface* ioDriver;
    
    // Encoder state tracking
    int lastEncoderA;
    int lastEncoderB;
    bool clockwiseRotationDetected;
    bool counterClockwiseRotationDetected;

public:
    Encoder();
    ~Encoder() = default;
    
    Encoder* setPinA(int pin);
    Encoder* setPinB(int pin);
    Encoder* setIoDriver(IoDriverInterface* driver);
    
    void update() override;
    bool rotatedClockwise() override;
    bool rotatedCounterClockwise() override;
};
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
    int currentEncoderA;
    int currentEncoderB;
    bool clockwiseRotationDetected;
    bool counterClockwiseRotationDetected;
    
    // Private helper methods for refactored update()
    bool isProperlyInitialized() const;
    void updateCurrentReadouts();
    bool aWentLow() const;
    bool bIsHigh() const;
    void detectClockwiseRotation();
    void detectCounterClockwiseRotation();
    void keepLastReadouts();

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
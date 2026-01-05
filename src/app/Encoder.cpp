#include "Encoder.h"
#include "IoDriverInterface.h"

Encoder::Encoder() : pinA(-1), pinB(-1), ioDriver(nullptr),
                     lastEncoderA(-1), lastEncoderB(-1),
                     clockwiseRotationDetected(false), counterClockwiseRotationDetected(false) {
}

Encoder* Encoder::setPinA(int pin) {
    this->pinA = pin;
    return this;
}

Encoder* Encoder::setPinB(int pin) {
    this->pinB = pin;
    return this;
}

Encoder* Encoder::setIoDriver(IoDriverInterface* driver) {
    this->ioDriver = driver;
    return this;
}

void Encoder::update() {
    if (pinA < 0 || pinB < 0 || !ioDriver) {
        return;
    }
    
    int currentA = ioDriver->digitalRead(pinA);
    int currentB = ioDriver->digitalRead(pinB);
    
    // Simple edge-based detection (copied from UserInput logic)
    if (lastEncoderA != currentA) {
        // A pin changed
        if (currentA == 0) { // A went LOW
            if (currentB == 1) {
                counterClockwiseRotationDetected = true;
            } else {
                clockwiseRotationDetected = true;
            }
        }
    }
    
    lastEncoderA = currentA;
    lastEncoderB = currentB;
}

bool Encoder::rotatedClockwise() {
    bool result = clockwiseRotationDetected;
    clockwiseRotationDetected = false; // Reset after reading
    return result;
}

bool Encoder::rotatedCounterClockwise() {
    bool result = counterClockwiseRotationDetected;
    counterClockwiseRotationDetected = false; // Reset after reading
    return result;
}
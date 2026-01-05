#include "Encoder.h"
#include "IoDriverInterface.h"

Encoder::Encoder() : pinA(-1), pinB(-1), ioDriver(nullptr),
                     lastEncoderA(-1), lastEncoderB(-1),
                     currentEncoderA(-1), currentEncoderB(-1),
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
    if (false == isProperlyInitialized()) {
        return;
    }

    updateCurrentReadouts();

    if (aWentLow() && bIsHigh()) {
        detectCounterClockwiseRotation();
        keepLastReadouts();
        return;
    } 
    
    if (aWentLow() && bIsLow()) {
        detectClockwiseRotation();
        keepLastReadouts();
        return;
    }
    
    if (false == aWentLow()) {
        keepLastReadouts();
        return;
    }
    
    // Should never get here
}

bool Encoder::isProperlyInitialized() const {
    return (pinA >= 0 && pinB >= 0 && ioDriver != nullptr);
}

void Encoder::updateCurrentReadouts() {
    currentEncoderA = ioDriver->digitalRead(pinA);
    currentEncoderB = ioDriver->digitalRead(pinB);
}

bool Encoder::aWentLow() const {
    return (lastEncoderA != currentEncoderA && currentEncoderA == 0);
}

bool Encoder::bIsHigh() const {
    return (currentEncoderB == 1);
}

bool Encoder::bIsLow() const {
    return (currentEncoderB == 0);
}

void Encoder::detectClockwiseRotation() {
    clockwiseRotationDetected = true;
    counterClockwiseRotationDetected = false;
}

void Encoder::detectCounterClockwiseRotation() {
    counterClockwiseRotationDetected = true;
    clockwiseRotationDetected = false;
}

void Encoder::keepLastReadouts() {
    lastEncoderA = currentEncoderA;
    lastEncoderB = currentEncoderB;
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
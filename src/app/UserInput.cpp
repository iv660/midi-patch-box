#include "UserInput.h"
#include "Button.h"

UserInput::UserInput(int userPin, int rightPin)
    : userPin(userPin), rightPin(rightPin), encoderPinA(-1), encoderPinB(-1), encoderButtonPin(-1), ioDriver(nullptr),
      lastEncoderA(1), lastEncoderB(1), clockwiseRotationDetected(false), counterClockwiseRotationDetected(false) {
    userButton = new Button(userPin);
    rightButton = new Button(rightPin);
    encoderButton = nullptr;
}

UserInput::UserInput(int userPin, int rightPin, int encoderPinA, int encoderPinB, int encoderButtonPin)
    : userPin(userPin), rightPin(rightPin), encoderPinA(encoderPinA), encoderPinB(encoderPinB), encoderButtonPin(encoderButtonPin), ioDriver(nullptr),
      lastEncoderA(1), lastEncoderB(1), clockwiseRotationDetected(false), counterClockwiseRotationDetected(false) {
    userButton = new Button(userPin);
    rightButton = new Button(rightPin);
    encoderButton = new Button(encoderButtonPin);
}

UserInput::~UserInput() {
    delete userButton;
    delete rightButton;
    delete encoderButton;
}

UserInput* UserInput::setIoDriver(IoDriverInterface* driver) {
    this->ioDriver = driver;
    if (userButton) {
        userButton->setIoDriver(driver);
    }
    if (rightButton) {
        rightButton->setIoDriver(driver);
    }
    if (encoderButton) {
        encoderButton->setIoDriver(driver);
    }
    
    // Configure encoder pins as INPUT_PULLUP if encoder is configured
    if (encoderPinA >= 0 && encoderPinB >= 0 && driver) {
        driver->pinMode(encoderPinA, 2); // INPUT_PULLUP = 2
        driver->pinMode(encoderPinB, 2); // INPUT_PULLUP = 2
    }
    
    return this;
}

void UserInput::update() {
    if (userButton) {
        userButton->update();
    }
    if (rightButton) {
        rightButton->update();
    }
    if (encoderButton) {
        encoderButton->update();
    }
    
    // Process encoder rotation if encoder pins are configured
    if (encoderPinA >= 0 && encoderPinB >= 0 && ioDriver) {
        updateEncoderRotation();
    }
}

bool UserInput::userButtonIsPressed() {
    return userButton ? userButton->isPressed() : false;
}

bool UserInput::rightButtonIsPressed() {
    return rightButton ? rightButton->isPressed() : false;
}

void UserInput::updateEncoderRotation() {
    int currentA = ioDriver->digitalRead(encoderPinA);
    int currentB = ioDriver->digitalRead(encoderPinB);
    
    // Quadrature encoder state machine
    // Clockwise: 11 -> 01 -> 00 -> 10 -> 11
    // Counter-clockwise: 11 -> 10 -> 00 -> 01 -> 11
    
    if (lastEncoderA != currentA || lastEncoderB != currentB) {
        // Detect clockwise rotation
        if ((lastEncoderA == 1 && lastEncoderB == 1 && currentA == 0 && currentB == 1) ||
            (lastEncoderA == 0 && lastEncoderB == 1 && currentA == 0 && currentB == 0) ||
            (lastEncoderA == 0 && lastEncoderB == 0 && currentA == 1 && currentB == 0) ||
            (lastEncoderA == 1 && lastEncoderB == 0 && currentA == 1 && currentB == 1)) {
            clockwiseRotationDetected = true;
        }
        
        // Detect counter-clockwise rotation
        if ((lastEncoderA == 1 && lastEncoderB == 1 && currentA == 1 && currentB == 0) ||
            (lastEncoderA == 1 && lastEncoderB == 0 && currentA == 0 && currentB == 0) ||
            (lastEncoderA == 0 && lastEncoderB == 0 && currentA == 0 && currentB == 1) ||
            (lastEncoderA == 0 && lastEncoderB == 1 && currentA == 1 && currentB == 1)) {
            counterClockwiseRotationDetected = true;
        }
    }
    
    lastEncoderA = currentA;
    lastEncoderB = currentB;
}

bool UserInput::encoderRotatedClockwise() {
    bool result = clockwiseRotationDetected;
    clockwiseRotationDetected = false; // Reset after reading
    return result;
}

bool UserInput::encoderRotatedCounterClockwise() {
    bool result = counterClockwiseRotationDetected;
    counterClockwiseRotationDetected = false; // Reset after reading
    return result;
}

bool UserInput::encoderButtonPressed() {
    return encoderButton ? encoderButton->isPressed() : false;
}
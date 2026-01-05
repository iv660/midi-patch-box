#include "UserInput.h"
#include "Button.h"
#include "Encoder.h"

UserInput::UserInput(int userPin, int rightPin)
    : userPin(userPin), rightPin(rightPin), encoderPinA(-1), encoderPinB(-1), encoderButtonPin(-1), ioDriver(nullptr) {
    userButton = new Button(userPin);
    rightButton = new Button(rightPin);
    encoderButton = nullptr;
    encoder = nullptr;
}

UserInput::UserInput(int userPin, int rightPin, int encoderPinA, int encoderPinB, int encoderButtonPin)
    : userPin(userPin), rightPin(rightPin), encoderPinA(encoderPinA), encoderPinB(encoderPinB), encoderButtonPin(encoderButtonPin), ioDriver(nullptr) {
    userButton = new Button(userPin);
    rightButton = new Button(rightPin);
    encoderButton = new Button(encoderButtonPin);
    encoder = new Encoder();
}

UserInput::~UserInput() {
    delete userButton;
    delete rightButton;
    delete encoderButton;
    delete encoder;
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
    
    // Configure encoder if present
    if (encoder && encoderPinA >= 0 && encoderPinB >= 0 && driver) {
        Encoder* concreteEncoder = static_cast<Encoder*>(encoder);
        concreteEncoder->setPinA(encoderPinA)->setPinB(encoderPinB)->setIoDriver(driver);
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
    if (hasEncoder()) {
        encoder->update();
    }
}

bool UserInput::hasEncoder() const {
    return encoder != nullptr;
}

bool UserInput::encoderRotatedClockwise() {
    return hasEncoder() ? encoder->rotatedClockwise() : false;
}

bool UserInput::encoderRotatedCounterClockwise() {
    return hasEncoder() ? encoder->rotatedCounterClockwise() : false;
}

bool UserInput::encoderButtonPressed() {
    return encoderButton ? encoderButton->isPressed() : false;
}
#include "UserInput.h"
#include "ButtonInterface.h"
#include "EncoderInterface.h"

UserInput::UserInput() : userButton(nullptr), rightButton(nullptr), encoderButton(nullptr), encoder(nullptr) {
}

UserInput::~UserInput() {
    // Don't delete injected dependencies - they are owned by the client
}

UserInput* UserInput::setUserButton(ButtonInterface* button) {
    this->userButton = button;
    return this;
}

UserInput* UserInput::setRightButton(ButtonInterface* button) {
    this->rightButton = button;
    return this;
}

UserInput* UserInput::setEncoderButton(ButtonInterface* button) {
    this->encoderButton = button;
    return this;
}

UserInput* UserInput::setEncoder(EncoderInterface* encoder) {
    this->encoder = encoder;
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
    
    if (hasEncoder()) {
        encoder->update();
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
    if (!hasEncoder()) {
        return false;
    }
    return encoder->rotatedClockwise();
}

bool UserInput::encoderRotatedCounterClockwise() {
    if (!hasEncoder()) {
        return false;
    }
    return encoder->rotatedCounterClockwise();
}

bool UserInput::encoderButtonPressed() {
    return encoderButton ? encoderButton->isPressed() : false;
}
#include "UserInput.h"
#include "Button.h"

UserInput::UserInput(int userPin, int rightPin)
    : userPin(userPin), rightPin(rightPin), ioDriver(nullptr) {
    userButton = new Button(userPin);
    rightButton = new Button(rightPin);
}

UserInput::~UserInput() {
    delete userButton;
    delete rightButton;
}

UserInput* UserInput::setIoDriver(IoDriverInterface* driver) {
    this->ioDriver = driver;
    if (userButton) {
        userButton->setIoDriver(driver);
    }
    if (rightButton) {
        rightButton->setIoDriver(driver);
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
}

bool UserInput::userButtonIsPressed() {
    return userButton ? userButton->isPressed() : false;
}

bool UserInput::rightButtonIsPressed() {
    return rightButton ? rightButton->isPressed() : false;
}
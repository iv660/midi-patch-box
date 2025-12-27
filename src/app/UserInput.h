#pragma once

#include "UserInputInterface.h"

class IoDriverInterface; // Forward declaration
class Button; // Forward declaration

class UserInput: public UserInputInterface {
private:
    int userPin;
    int rightPin;
    IoDriverInterface* ioDriver;
    Button* userButton;
    Button* rightButton;

public:
    UserInput(int userPin = 24, int rightPin = 25);
    ~UserInput();
    UserInput* setIoDriver(IoDriverInterface* driver);
    void update() override;
    bool userButtonIsPressed() override;
    bool rightButtonIsPressed() override;
};
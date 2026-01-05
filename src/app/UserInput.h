#pragma once

#include "UserInputInterface.h"

class IoDriverInterface; // Forward declaration
class Button; // Forward declaration
class EncoderInterface; // Forward declaration

class UserInput: public UserInputInterface {
private:
    int userPin;
    int rightPin;
    int encoderPinA;
    int encoderPinB;
    int encoderButtonPin;
    IoDriverInterface* ioDriver;
    Button* userButton;
    Button* rightButton;
    Button* encoderButton;
    EncoderInterface* encoder;
    
    void updateEncoderRotation();
    bool hasEncoder() const;

public:
    UserInput(int userPin = 24, int rightPin = 15);
    UserInput(int userPin, int rightPin, int encoderPinA, int encoderPinB, int encoderButtonPin);
    ~UserInput();
    UserInput* setIoDriver(IoDriverInterface* driver);
    void update() override;
    bool userButtonIsPressed() override;
    bool rightButtonIsPressed() override;
    bool encoderRotatedClockwise() override;
    bool encoderRotatedCounterClockwise() override;
    bool encoderButtonPressed() override;
};
#pragma once

#include "UserInputInterface.h"

class ButtonInterface; // Forward declaration
class EncoderInterface; // Forward declaration

class UserInput: public UserInputInterface {
private:
    ButtonInterface* userButton;
    ButtonInterface* rightButton;
    ButtonInterface* encoderButton;
    EncoderInterface* encoder;
    
    void updateEncoderRotation();
    bool hasEncoder() const;

public:
    UserInput();
    ~UserInput();
    UserInput* setUserButton(ButtonInterface* button);
    UserInput* setRightButton(ButtonInterface* button);
    UserInput* setEncoderButton(ButtonInterface* button);
    UserInput* setEncoder(EncoderInterface* encoder);
    void update() override;
    bool userButtonIsPressed() override;
    bool rightButtonIsPressed() override;
    bool encoderRotatedClockwise() override;
    bool encoderRotatedCounterClockwise() override;
    bool encoderButtonPressed() override;
    bool encoderButtonLongPressed() override;
};
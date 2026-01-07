#pragma once

class UserInputInterface {
public:
    virtual void update() = 0;
    virtual bool userButtonIsPressed() = 0;
    virtual bool rightButtonIsPressed() = 0;
    virtual bool encoderRotatedClockwise() = 0;
    virtual bool encoderRotatedCounterClockwise() = 0;
    virtual bool encoderButtonPressed() = 0;
    virtual bool encoderButtonLongPressed() = 0;
};

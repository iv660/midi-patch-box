#pragma once

class UserInputInterface {
public:
    virtual bool userButtonIsPressed() = 0;
    virtual bool rightButtonIsPressed() = 0;
};

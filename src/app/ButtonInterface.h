#pragma once

class ButtonInterface {
public:
    virtual ~ButtonInterface() = default;
    virtual void update() = 0;
    virtual bool isPressed() = 0;
    virtual bool isLongPressed() = 0;
    virtual ButtonInterface* enableLongPressDetection() = 0;
};
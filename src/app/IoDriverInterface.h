#pragma once

class IoDriverInterface {
public:
    virtual ~IoDriverInterface() = default;
    virtual int digitalRead(int pin) = 0;
    virtual void delay(unsigned long ms) = 0;
    virtual unsigned long millis() = 0;
};
#pragma once

class IoDriverInterface {
public:
    static const int INPUT_PULLUP = 2;
    
    virtual ~IoDriverInterface() = default;
    virtual int digitalRead(int pin) = 0;
    virtual void delay(unsigned long ms) = 0;
    virtual unsigned long millis() = 0;
    virtual void pinMode(int pin, int mode) = 0;
};
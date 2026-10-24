#pragma once

#include "app/IoDriverInterface.h"

class ArduinoIoDriver : public IoDriverInterface {
public:
    int digitalRead(int pin) override;
    void delay(unsigned long ms) override;
    unsigned long millis() override;
    void pinMode(int pin, int mode) override;
};
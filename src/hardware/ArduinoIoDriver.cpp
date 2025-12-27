#include "ArduinoIoDriver.h"
#include <Arduino.h>

int ArduinoIoDriver::digitalRead(int pin) {
    return ::digitalRead(pin);
}

void ArduinoIoDriver::delay(unsigned long ms) {
    ::delay(ms);
}

unsigned long ArduinoIoDriver::millis() {
    return ::millis();
}

void ArduinoIoDriver::pinMode(int pin, int mode) {
    ::pinMode(pin, static_cast<PinMode>(mode));
}
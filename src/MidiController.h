#pragma once

#include <Adafruit_TinyUSB.h>

class MidiController
{
public:
    MidiController();
    void sendProgramChange(uint8_t program, uint8_t channel);
    void begin();

private:
    Adafruit_USBD_MIDI usbMIDI;
};

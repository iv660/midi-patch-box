#pragma once

#include <Adafruit_TinyUSB.h>

class MidiController
{
private:
    Adafruit_USBD_MIDI usbMIDI;
    uint8_t channel;
    
public:
    MidiController(uint8_t channel): channel(channel) {};
    void sendProgramChange(uint8_t program);
    void begin();
};

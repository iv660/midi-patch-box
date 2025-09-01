#pragma once

#include <Adafruit_TinyUSB.h>
#include "app/MidiControllerInterface.h"

class MidiController: public MidiControllerInterface
{
private:
    Adafruit_USBD_MIDI usbMIDI;
    int channel;
    
public:
    MidiController(int channel): channel(channel) {};
    void sendProgramChange(int program);
    void begin();
};

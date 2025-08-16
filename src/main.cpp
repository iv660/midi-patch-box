#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "MidiController.h"
#include "UserInput.h"

const uint8_t MIDI_CHANNEL = 0;
bool programToggle = false; // false = program 2, true = program 42

MidiController midiController(MIDI_CHANNEL);
UserInput userInput;

void setup()
{
    // Set manufacturer and product descriptors BEFORE USB initialization
    USBDevice.setManufacturerDescriptor("iv660");
    USBDevice.setProductDescriptor("MIDI Patch Box");
    USBDevice.setSerialDescriptor("0001"); // any serial number

    midiController.begin();
}

void loop() {
    userInput.update();

    if (userInput.usrButtonIsPressed()) {
        uint8_t program = programToggle ? 41 : 1; // 42nd or 2nd program
        midiController.sendProgramChange(program);
        programToggle = !programToggle;
    }
}

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "app/MidiPatchBoxApplication.h"
#include "app/ProgramSelector.h"
#include "app/UserInput.h"
#include "hardware/MidiController.h"
#include "hardware/ArduinoIoDriver.h"
#include "hardware/DisplayProgramSelectionView.h"


const uint8_t MIDI_CHANNEL = 0;

MidiPatchBoxApplication app;

ProgramSelector programSelector;
UserInput userInput;
MidiController midiController(MIDI_CHANNEL);
ArduinoIoDriver ioDriver;
DisplayProgramSelectionView displayView;

void setup()
{
    // Set manufacturer and product descriptors BEFORE USB initialization
    USBDevice.setManufacturerDescriptor("iv660");
    USBDevice.setProductDescriptor("MIDI Patch Box");
    USBDevice.setSerialDescriptor("0001"); // any serial number
    
    programSelector.setPrograms({0, 41, 112});
    
    userInput.setIoDriver(&ioDriver);

    app.setProgramSelector(&programSelector)
        ->setUserInput(&userInput)
        ->setMidiController(&midiController)
        ->setProgramSelectionView(&displayView)
        ->begin();
}

void loop() {
    app.tick();
}

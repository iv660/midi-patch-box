#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "MidiController.h"
#include "UserInput.h"

// Встроенная кнопка
const uint8_t BUTTON_PIN = 24;
const uint8_t MIDI_CHANNEL = 0;
bool programToggle = false; // false = программа 2, true = программа 42

MidiController midiController(MIDI_CHANNEL);
UserInput userInput;

void setup()
{
    // Задать имя производителя и продукта ДО начала USB
    USBDevice.setManufacturerDescriptor("iv660");
    USBDevice.setProductDescriptor("MIDI Patch Box");
    USBDevice.setSerialDescriptor("0001"); // можно задать любой серийник

    midiController.begin();
}

void loop() {
    userInput.update();

    if (userInput.usrButtonIsPressed()) {
        uint8_t program = programToggle ? 41 : 1; // 42-я или 2-я программа
        midiController.sendProgramChange(program);
        programToggle = !programToggle;
    }
}
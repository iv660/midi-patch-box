#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include "MidiController.h"

MidiController midiController;

// Встроенная кнопка
const uint8_t BUTTON_PIN = 24;
bool lastButtonState = HIGH;
bool programToggle = false; // false = программа 2, true = программа 42

void setup()
{
    // Задать имя производителя и продукта ДО начала USB
    USBDevice.setManufacturerDescriptor("iv660");
    USBDevice.setProductDescriptor("MIDI Patch Box");
    USBDevice.setSerialDescriptor("0001"); // можно задать любой серийник

    pinMode(BUTTON_PIN, INPUT_PULLUP);

    midiController.begin();
}

void loop()
{
    bool currentState = digitalRead(BUTTON_PIN);

    // Обработка нажатия
    if (lastButtonState == HIGH && currentState == LOW)
    {
        uint8_t channel = 0;                      // MIDI канал 1 (нумерация с 0)
        uint8_t program = programToggle ? 41 : 1; // 42-я или 2-я программа
        midiController.sendProgramChange(program, channel);
        programToggle = !programToggle;
    }

    lastButtonState = currentState;
}

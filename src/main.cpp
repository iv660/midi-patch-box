#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

Adafruit_USBD_MIDI usbMIDI;

void setup() {
  usbMIDI.begin();
}

void loop() {
  // Ничего не отправляем/не принимаем — только чтобы Windows увидел устройство
}

#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

Adafruit_USBD_MIDI usbMIDI;

const uint8_t BUTTON_PIN = 24; // встроенная кнопка на Pico
bool lastButtonState = HIGH;
bool programToggle = false; // false = программа 2, true = программа 8

void sendProgramChange(uint8_t program, uint8_t channel) {
  uint8_t packet[4];
  packet[0] = (0 << 4) | 0xC;      // CN=0, CIN=0xC (Program Change)
  packet[1] = 0xC0 | (channel & 0x0F); // статус байт
  packet[2] = program & 0x7F;      // номер программы
  packet[3] = 0;                   // не используется
  usbMIDI.writePacket(packet);
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  usbMIDI.begin();
}

void loop() {
  bool currentState = digitalRead(BUTTON_PIN);

  // Обработка нажатия
  if (lastButtonState == HIGH && currentState == LOW) {
    uint8_t channel = 0; // MIDI канал 1 (нумерация с 0)
    uint8_t program = programToggle ? 41 : 1; // 42-я или 2-я программа
    sendProgramChange(program, channel);
    programToggle = !programToggle;
  }

  lastButtonState = currentState;
}

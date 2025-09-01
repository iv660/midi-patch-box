#include "MidiController.h"

void MidiController::sendProgramChange(int program)
{
    uint8_t packet[4];
    packet[0] = (0 << 4) | 0xC;          // CN=0, CIN=0xC (Program Change)
    packet[1] = 0xC0 | (channel & 0x0F); // статус байт
    packet[2] = program & 0x7F;          // номер программы
    packet[3] = 0;                       // пустой байт
    usbMIDI.writePacket(packet);
}

void MidiController::begin()
{
    usbMIDI.begin();
}

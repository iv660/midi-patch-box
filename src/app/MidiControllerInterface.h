#pragma once

class MidiControllerInterface {
public:
    virtual void sendProgramChange(int program) = 0;
};

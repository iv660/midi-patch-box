#pragma once

class EncoderInterface {
public:
    virtual ~EncoderInterface() = default;
    virtual void update() = 0;
    virtual bool rotatedClockwise() = 0;
    virtual bool rotatedCounterClockwise() = 0;
};
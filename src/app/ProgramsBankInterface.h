#pragma once

class ProgramsBankInterface {
public:
    virtual ~ProgramsBankInterface() = default;
    virtual ProgramsBankInterface* addProgram(int programNumber, const char* programName) = 0;
    virtual const char* getProgramName(int programNumber) = 0;
};
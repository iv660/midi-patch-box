#pragma once
#include "Program.h"

class ProgramsBankInterface {
public:
    virtual ~ProgramsBankInterface() = default;
    virtual ProgramsBankInterface* addProgram(int programNumber, const char* programName) = 0;
    virtual const char* getProgramName(int programNumber) = 0;
    virtual const Program* getAllPrograms(int& count) const = 0;
};
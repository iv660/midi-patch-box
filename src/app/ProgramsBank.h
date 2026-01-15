#pragma once

#include "ProgramsBankInterface.h"
#include "Program.h"

class ProgramsBank : public ProgramsBankInterface {
public:
    ProgramsBank();
    
    ProgramsBankInterface* addProgram(int programNumber, const char* programName) override;
    const char* getProgramName(int programNumber) override;
    const Program* getAllPrograms(int& count) const override;

private:
    static const int MAX_PROGRAMS = 128;
    Program programs[MAX_PROGRAMS];
    int programCount;
};
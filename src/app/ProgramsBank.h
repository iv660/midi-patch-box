#pragma once

#include "ProgramsBankInterface.h"

class ProgramsBank : public ProgramsBankInterface {
public:
    struct Program {
        int number;
        char name[17];
    };
    
    ProgramsBank();
    
    ProgramsBankInterface* addProgram(int programNumber, const char* programName) override;
    const char* getProgramName(int programNumber) override;

private:
    static const int MAX_PROGRAMS = 128;
    Program programs[MAX_PROGRAMS];
    int programCount;
};
#include "ProgramsBank.h"
#include <string.h>

ProgramsBank::ProgramsBank() : programCount(0) {}

ProgramsBankInterface* ProgramsBank::addProgram(int programNumber, const char* programName) {
    if (programCount < MAX_PROGRAMS) {
        programs[programCount].number = programNumber;
        strncpy(programs[programCount].name, programName, 16);
        programs[programCount].name[16] = '\0';
        programCount++;
    }
    return this;
}

const char* ProgramsBank::getProgramName(int programNumber) {
    for (int i = 0; i < programCount; i++) {
        if (programs[i].number == programNumber) {
            return programs[i].name;
        }
    }
    return "";
}

const Program* ProgramsBank::getAllPrograms(int& count) const
{
    count = programCount;
    return programs;
}
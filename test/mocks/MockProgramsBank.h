#pragma once
#include "../../src/app/ProgramsBankInterface.h"
#include "../../src/app/Program.h"
#include <string.h>

class MockProgramsBank : public ProgramsBankInterface {
private:
    Program programs[128];
    int programCount = 0;

public:
    ProgramsBankInterface* addProgram(int programNumber, const char* programName) override {
        if (programCount < 128) {
            programs[programCount].number = programNumber;
            strncpy(programs[programCount].name, programName, 16);
            programs[programCount].name[16] = '\0';
            programCount++;
        }
        return this;
    }
    
    const char* getProgramName(int programNumber) override {
        for (int i = 0; i < programCount; i++) {
            if (programs[i].number == programNumber) {
                return programs[i].name;
            }
        }
        return "";
    }
    
    const Program* getAllPrograms(int& count) const override {
        count = programCount;
        return programs;
    }
    
    // Test helper methods
    const Program* getPrograms() const { return programs; }
    int getProgramCount() const { return programCount; }
};
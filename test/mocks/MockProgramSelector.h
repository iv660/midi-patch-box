#pragma once
#include "../../src/app/ProgramSelectorInterface.h"
#include <initializer_list>

class MockProgramSelector : public ProgramSelectorInterface {
private:
    int programs[128];
    int programCount = 0;
    int selectedIndex = 0;

public:
    void selectNextProgram() override {
        if (programCount > 0) {
            selectedIndex = (selectedIndex + 1) % programCount;
        }
    }
    
    void selectPreviousProgram() override {
        if (programCount > 0) {
            selectedIndex = (selectedIndex - 1 + programCount) % programCount;
        }
    }
    
    int getSelectedProgramNumber() const override {
        if (programCount > 0 && selectedIndex < programCount) {
            return programs[selectedIndex];
        }
        return 0;
    }
    
    ProgramSelectorInterface* setPrograms(std::initializer_list<int> programList) override {
        programCount = 0;
        for (int program : programList) {
            if (programCount < 128) {
                programs[programCount++] = program;
            }
        }
        selectedIndex = 0;
        return this;
    }
    
    void updateProgram(int index, int programNumber) override {
        if (index >= 0 && index < programCount) {
            programs[index] = programNumber;
        }
    }
    
    // Test helper methods
    const int* getProgramsList() const { return programs; }
    int getProgramCount() const { return programCount; }
    int getSelectedIndex() const { return selectedIndex; }
};
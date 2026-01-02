#pragma once

#include <initializer_list>

class ProgramSelectorInterface {
public:
    virtual void selectNextProgram() = 0;
    virtual void selectPreviousProgram() = 0;
    virtual int getSelectedProgramNumber() const = 0;
    virtual ProgramSelectorInterface* setPrograms(std::initializer_list<int> programs) = 0;
};

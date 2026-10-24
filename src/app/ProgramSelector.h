#pragma once

#include <initializer_list>
#include "ProgramSelectorInterface.h"

class ProgramSelector: public ProgramSelectorInterface 
{
public:
    ProgramSelector();
    ~ProgramSelector();

    ProgramSelector(const ProgramSelector&) = delete;
    ProgramSelector& operator=(const ProgramSelector&) = delete;
    ProgramSelector(ProgramSelector&&) = delete;
    ProgramSelector& operator=(ProgramSelector&&) = delete;

    void selectNextProgram() override;
    void selectPreviousProgram() override;
    int getSelectedProgramNumber() const override;
    ProgramSelectorInterface* setPrograms(std::initializer_list<int> programs) override;
    ProgramSelectorInterface* setPrograms(const int* programs, int count) override;
    void updateProgram(int index, int programNumber) override;

private:
    int programsListPointer;
    int* programsList;
    int programsCount;

    void selectFirstProgram();
    bool lastProgramIsSelected() const;
    int getProgramsCount() const;
};
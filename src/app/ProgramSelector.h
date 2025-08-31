#pragma once

#include "ProgramSelectorInterface.h"

class ProgramSelector: public ProgramSelectorInterface 
{
public:
    ProgramSelector();

    void selectNextProgram() override;
    int getSelectedProgramNumber() const override;

private:
    int selectedProgramNumber;
    const int maxPrograms;

    void selectFirstProgram();
    bool lastProgramIsSelected() const;
};
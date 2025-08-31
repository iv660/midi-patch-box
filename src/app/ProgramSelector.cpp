#include "ProgramSelector.h"

ProgramSelector::ProgramSelector()
    : selectedProgramNumber(0)
    , maxPrograms(3)
{
}

void ProgramSelector::selectFirstProgram()
{
    selectedProgramNumber = 0;
}

bool ProgramSelector::lastProgramIsSelected() const
{
    return selectedProgramNumber == (maxPrograms - 1);
}

void ProgramSelector::selectNextProgram()
{
    if (lastProgramIsSelected()) {
        selectFirstProgram();
        return;
    }

    selectedProgramNumber++;
}

int ProgramSelector::getSelectedProgramNumber() const
{
    return selectedProgramNumber;
}
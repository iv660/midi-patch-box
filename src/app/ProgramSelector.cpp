#include "ProgramSelector.h"

ProgramSelector::ProgramSelector()
    : programsListPointer(0),
      programsList(nullptr),
      programsCount(0)
{
}

ProgramSelector::~ProgramSelector()
{
    delete[] programsList;
}

void ProgramSelector::selectFirstProgram()
{
    programsListPointer = 0;
}

bool ProgramSelector::lastProgramIsSelected() const
{
    if (programsCount == 0) {
        return false;
    }
    return programsListPointer == (programsCount - 1);
}

int ProgramSelector::getProgramsCount() const
{
    return programsCount;
}

void ProgramSelector::selectNextProgram()
{
    if (programsCount == 0) {
        return;
    }

    if (lastProgramIsSelected()) {
        selectFirstProgram();
        return;
    }

    programsListPointer++;
}

int ProgramSelector::getSelectedProgramNumber() const
{
    if (programsCount == 0) {
        return 0;
    }
    if (programsList == nullptr) {
        return 0;
    }
    if (programsListPointer < 0) {
        return 0;
    }
    if (programsListPointer >= programsCount) {
        return 0;
    }

    return programsList[programsListPointer];
}

ProgramSelectorInterface * ProgramSelector::setPrograms(std::initializer_list<int> programs)
{
    // Free the old buffer
    delete[] programsList;
    programsCount = static_cast<int>(programs.size());

    if (programsCount == 0) {
        programsList = nullptr;
        selectFirstProgram();
        return this;
    }

    programsList = new int[programsCount];
    
    int i = 0;
    for (int v : programs) {
        programsList[i++] = v;
    }

    selectFirstProgram();
    return this;
}


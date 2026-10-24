#pragma once

class ProgramSelectionViewInterface {
public:
    virtual ~ProgramSelectionViewInterface() = default;
    virtual ProgramSelectionViewInterface* setSelectedProgramNumber(int programNumber) = 0;
    virtual ProgramSelectionViewInterface* displayProgramName(const char* programName) = 0;
    virtual ProgramSelectionViewInterface* highlightProgram() = 0;
    virtual ProgramSelectionViewInterface* clearHighlight() = 0;
};
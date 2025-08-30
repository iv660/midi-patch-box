#pragma once

class ProgramSelectorInterface {
public:
    virtual void selectNextProgram() = 0;
    virtual int getSelectedProgram() const = 0;
};

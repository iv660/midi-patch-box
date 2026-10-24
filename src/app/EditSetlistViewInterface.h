#pragma once
#include "Program.h"

class EditSetlistViewInterface {
public:
    virtual ~EditSetlistViewInterface() = default;
    
    // Display the setlist
    virtual void showSetlist(Program* setlist) = 0;
    
    // Set the currently selected item index
    virtual void setSelectedItemIndex(int index) = 0;
    
    // Enable/disable edit mode for a specific program
    virtual void setEditMode(bool enabled) = 0;
    
    // Update the program being edited
    virtual void setEditedProgramIndex(int index) = 0;
    virtual void setEditedProgramNumber(int programNumber) = 0;
    virtual void setEditedProgramName(const char* programName) = 0;
};
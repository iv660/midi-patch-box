#pragma once
#include "../../src/app/EditSetlistViewInterface.h"
#include "../../src/app/Program.h"
#include <cstring>

class MockEditSetlistView : public EditSetlistViewInterface {
private:
    bool showSetlistCalled = false;
    Program displayedSetlist[10];
    int selectedItemIndex = 0;
    bool editMode = false;
    bool lastEditModeValue = false;  // Track last value passed to setEditMode
    int editedProgramIndex = 0;
    int editedProgramNumber = 0;
    char editedProgramName[17] = "";

public:
    // Interface methods
    void showSetlist(Program* setlist) override {
        showSetlistCalled = true;
        // Copy setlist for testing
        for (int i = 0; i < 10; i++) {
            displayedSetlist[i] = setlist[i];
        }
    }

    void setSelectedItemIndex(int index) override {
        selectedItemIndex = index;
    }

    void setEditMode(bool enabled) override {
        editMode = enabled;
        lastEditModeValue = enabled;
    }
    
    void setEditedProgramIndex(int index) override {
        editedProgramIndex = index;
    }
    
    void setEditedProgramNumber(int programNumber) override {
        editedProgramNumber = programNumber;
    }
    
    void setEditedProgramName(const char* programName) override {
        strncpy(editedProgramName, programName, 16);
        editedProgramName[16] = '\0';
    }
    
    // Test helper methods
    bool showSetlistWasCalled() const { return showSetlistCalled; }
    const Program* getDisplayedSetlistItems() const { return displayedSetlist; }
    int getSelectedItemIndex() const { return selectedItemIndex; }
    bool editModeIsOn() const { return editMode; }
    bool getLastEditModeValue() const { return lastEditModeValue; }
    int getSetlistEditedProgramIndex() const { return editedProgramIndex; }
    int getSetlistEditedProgramNumber() const { return editedProgramNumber; }
    const char* getSetlistEditedProgramName() const { return editedProgramName; }
};
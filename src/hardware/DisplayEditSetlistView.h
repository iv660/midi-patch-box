#pragma once

#include "app/EditSetlistViewInterface.h"
#include "app/Program.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <cstring>

class DisplayEditSetlistView : public EditSetlistViewInterface
{
public:
    DisplayEditSetlistView(int sda_pin = 20, int scl_pin = 21, uint8_t i2c_address = 0x3C);
    ~DisplayEditSetlistView();

    DisplayEditSetlistView(const DisplayEditSetlistView&) = delete;
    DisplayEditSetlistView& operator=(const DisplayEditSetlistView&) = delete;
    DisplayEditSetlistView(DisplayEditSetlistView&&) = delete;
    DisplayEditSetlistView& operator=(DisplayEditSetlistView&&) = delete;

    void showSetlist(Program* setlist) override;
    void setSelectedItemIndex(int index) override;
    void setEditMode(bool enabled) override;
    void setEditedProgramIndex(int index) override;
    void setEditedProgramNumber(int programNumber) override;
    void setEditedProgramName(const char* programName) override;

private:
    static constexpr int SCREEN_WIDTH = 128;
    static constexpr int SCREEN_HEIGHT = 64;
    static constexpr int OLED_RESET = -1;
    static constexpr int MAX_PROGRAM_NAME_LENGTH = 16;
    static constexpr int MAX_SETLIST_SIZE = 16;
    static constexpr int VISIBLE_ITEMS = 4;  // How many items fit on screen
    
    void initializeDisplay();
    void updateDisplay();
    void drawSetlistMode();
    void drawSetlistItem(int y, int index, bool isSelected, bool isEditing);
    void drawEditMode();
    int getScrollOffset() const;
    
    Adafruit_SSD1306 display;
    bool isInitialized;
    
    // Setlist data
    Program setlist[MAX_SETLIST_SIZE];
    int setlistSize;
    int selectedIndex;
    
    // Edit mode state
    bool editModeEnabled;
    int editedIndex;
    int editedProgramNumber;
    char editedProgramName[MAX_PROGRAM_NAME_LENGTH + 1];
    
    // Display configuration
    int sdaPin;
    int sclPin;
    uint8_t i2cAddress;

    void copySetlistData(Program* sourceSetlist);
    void addBackItemAtBeginning();
};
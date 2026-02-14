#include "DisplayEditSetlistView.h"
#include <Arduino.h>
#include <cstring>

DisplayEditSetlistView::DisplayEditSetlistView(int sda_pin, int scl_pin, uint8_t i2c_address)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
    , isInitialized(false)
    , setlistSize(0)
    , selectedIndex(0)
    , editModeEnabled(false)
    , editedIndex(-1)
    , editedProgramNumber(0)
    , sdaPin(sda_pin)
    , sclPin(scl_pin)
    , i2cAddress(i2c_address)
{
    editedProgramName[0] = '\0';
    initializeDisplay();
}

DisplayEditSetlistView::~DisplayEditSetlistView()
{
    if (isInitialized) {
        display.clearDisplay();
        display.display();
    }
}

void DisplayEditSetlistView::initializeDisplay()
{
    Wire.setSDA(sdaPin);
    Wire.setSCL(sclPin);
    Wire.begin();
    
    if (display.begin(SSD1306_SWITCHCAPVCC, i2cAddress)) {
        isInitialized = true;
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.display();
    }
}

void DisplayEditSetlistView::copySetlistData(Program* sourceSetlist)
{
    setlistSize = 0;
    for (int i = 0; i < MAX_SETLIST_SIZE && sourceSetlist[i].number >= 0; i++) {
        setlist[i] = sourceSetlist[i];
        setlistSize++;
    }
}

void DisplayEditSetlistView::addBackItemAtBeginning()
{
    if (setlistSize < MAX_SETLIST_SIZE) {
        for (int i = setlistSize; i > 0; --i) {
            setlist[i] = setlist[i-1];
        }
        setlist[0].number = -1;
        strncpy(setlist[0].name, "Back", sizeof(setlist[0].name) - 1);
        setlist[0].name[sizeof(setlist[0].name) - 1] = '\0';
        setlistSize++;
    }
}

void DisplayEditSetlistView::showSetlist(Program* setlist)
{
    if (setlist == nullptr) {
        setlistSize = 0;
        updateDisplay();
        return;
    }

    copySetlistData(setlist);
    addBackItemAtBeginning();

    selectedIndex = 0;
    updateDisplay();
}

void DisplayEditSetlistView::setSelectedItemIndex(int index)
{
    if (index >= 0 && index < setlistSize) {
        selectedIndex = index;
        updateDisplay();
    }
}

void DisplayEditSetlistView::setEditMode(bool enabled)
{
    editModeEnabled = enabled;
    updateDisplay();
}

void DisplayEditSetlistView::setEditedProgramIndex(int index)
{
    editedIndex = index;
    updateDisplay();
}

void DisplayEditSetlistView::setEditedProgramNumber(int programNumber)
{
    editedProgramNumber = programNumber;
    updateDisplay();
}

void DisplayEditSetlistView::setEditedProgramName(const char* programName)
{
    if (programName != nullptr) {
        strncpy(editedProgramName, programName, MAX_PROGRAM_NAME_LENGTH);
        editedProgramName[MAX_PROGRAM_NAME_LENGTH] = '\0';
    } else {
        editedProgramName[0] = '\0';
    }
    updateDisplay();
}

void DisplayEditSetlistView::updateDisplay()
{
    if (!isInitialized) {
        return;
    }

    display.clearDisplay();

    if (editModeEnabled) {
        drawEditMode();
    } else {
        drawSetlistMode();
    }

    display.display();
}

void DisplayEditSetlistView::drawSetlistMode()
{
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Edit Setlist:");

    int scrollOffset = getScrollOffset();

    for (int i = 0; i < VISIBLE_ITEMS && (i + scrollOffset) < setlistSize; i++) {
        int itemIndex = i + scrollOffset;
        int y = 12 + i * 12;  // 12 pixels per line
        drawSetlistItem(y, itemIndex, itemIndex == selectedIndex, false);
    }
}

void DisplayEditSetlistView::drawSetlistItem(int y, int index, bool isSelected, bool isEditing)
{
    if (index >= setlistSize) {
        return;
    }
    
    display.setCursor(0, y);
    display.setTextSize(1);
    
    // Draw selection indicator
    if (isSelected) {
        display.print(">");
    } else {
        display.print(" ");
    }
    
    // Draw program info
    if (setlist[index].number == -1) {
        // Back item
        display.print("Back");
    } else {
        display.print(setlist[index].number);
        display.print(" ");
        if (strlen(setlist[index].name) > 0) {
            display.print(setlist[index].name);
        }
    }
}

void DisplayEditSetlistView::drawEditMode()
{
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Edit Program:");
    
    display.setCursor(0, 16);
    display.print("Prog: ");
    display.print(editedProgramNumber);
    
    display.setCursor(0, 28);
    display.print("Name: ");
    if (strlen(editedProgramName) > 0) {
        display.print(editedProgramName);
    } else {
        display.print("(none)");
    }
    
    // Draw blinking cursor or edit indicator
    display.setCursor(0, 44);
    display.print("Press to save");
}

int DisplayEditSetlistView::getScrollOffset() const
{
    if (setlistSize <= VISIBLE_ITEMS) {
        return 0;
    }
    
    // Keep selected item visible
    if (selectedIndex < VISIBLE_ITEMS / 2) {
        return 0;
    }
    
    if (selectedIndex >= setlistSize - VISIBLE_ITEMS / 2) {
        return setlistSize - VISIBLE_ITEMS;
    }
    
    return selectedIndex - VISIBLE_ITEMS / 2;
}
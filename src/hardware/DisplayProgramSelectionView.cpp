#include "DisplayProgramSelectionView.h"
#include <Arduino.h>
#include <cstring>

DisplayProgramSelectionView::DisplayProgramSelectionView(int sda_pin, int scl_pin, uint8_t i2c_address)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
    , isInitialized(false)
    , lastProgramNumber(-1)
    , hasProgramName(false)
    , sdaPin(sda_pin)
    , sclPin(scl_pin)
    , i2cAddress(i2c_address)
{
    programName[0] = '\0';
    initializeDisplay();
}

DisplayProgramSelectionView::~DisplayProgramSelectionView()
{
    if (isInitialized) {
        display.clearDisplay();
        display.display();
    }
}

ProgramSelectionViewInterface* DisplayProgramSelectionView::setSelectedProgramNumber(int programNumber)
{
    if (programNumber != lastProgramNumber) {
        lastProgramNumber = programNumber;
        updateDisplay();
    }
    
    return this;
}

ProgramSelectionViewInterface* DisplayProgramSelectionView::displayProgramName(const char* programName)
{
    if (programName != nullptr && strlen(programName) > 0) {
        strncpy(this->programName, programName, MAX_PROGRAM_NAME_LENGTH);
        this->programName[MAX_PROGRAM_NAME_LENGTH] = '\0';
        hasProgramName = true;
    } else {
        this->programName[0] = '\0';
        hasProgramName = false;
    }
    
    updateDisplay();
    return this;
}

void DisplayProgramSelectionView::initializeDisplay()
{
    // Initialize I2C communication with custom pins
    Wire.setSDA(sdaPin);
    Wire.setSCL(sclPin);
    Wire.begin();
    
    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, i2cAddress)) {
        Serial.println(F("SSD1306 allocation failed"));
        return;
    }
    
    isInitialized = true;
}

void DisplayProgramSelectionView::clearDisplay()
{
    if (!isInitialized) return;
    
    display.clearDisplay();
}

void DisplayProgramSelectionView::displayProgramNumber(int programNumber)
{
    lastProgramNumber = programNumber;
}

void DisplayProgramSelectionView::updateDisplay()
{
    if (!isInitialized || lastProgramNumber < 0) return;
    
    clearDisplay();
    
    // Display program number in large font (center of screen)
    display.setTextSize(4);
    display.setTextColor(SSD1306_WHITE);
    
    // Calculate center position for program number
    int16_t x1, y1;
    uint16_t w, h;
    String progStr = String(lastProgramNumber);
    display.getTextBounds(progStr, 0, 0, &x1, &y1, &w, &h);
    int centerX = (SCREEN_WIDTH - w) / 2;
    int centerY = (SCREEN_HEIGHT - h) / 2 - 8;
    
    display.setCursor(centerX, centerY);
    display.print(lastProgramNumber);
    
    // Add program name at bottom if available, otherwise nothing
    display.setTextSize(1);
    
    if (hasProgramName && strlen(programName) > 0) {
        display.getTextBounds(programName, 0, 0, &x1, &y1, &w, &h);
        int labelX = (SCREEN_WIDTH - w) / 2;
        display.setCursor(labelX, SCREEN_HEIGHT - h - 4);
        display.print(programName);
    }
    // If no program name is set, display nothing at the bottom
    
    // Update the display
    display.display();
}

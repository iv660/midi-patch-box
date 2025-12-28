#pragma once

#include "app/ProgramSelectionViewInterface.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class DisplayProgramSelectionView : public ProgramSelectionViewInterface
{
public:
    DisplayProgramSelectionView(int sda_pin = 20, int scl_pin = 21, uint8_t i2c_address = 0x3C);
    ~DisplayProgramSelectionView();

    DisplayProgramSelectionView(const DisplayProgramSelectionView&) = delete;
    DisplayProgramSelectionView& operator=(const DisplayProgramSelectionView&) = delete;
    DisplayProgramSelectionView(DisplayProgramSelectionView&&) = delete;
    DisplayProgramSelectionView& operator=(DisplayProgramSelectionView&&) = delete;

    ProgramSelectionViewInterface* setSelectedProgramNumber(int programNumber) override;
    ProgramSelectionViewInterface* displayProgramName(const char* programName) override;

private:
    static constexpr int SCREEN_WIDTH = 128;
    static constexpr int SCREEN_HEIGHT = 64;
    static constexpr int OLED_RESET = -1;
    static constexpr int MAX_PROGRAM_NAME_LENGTH = 16;
    
    void initializeDisplay();
    void clearDisplay();
    void displayProgramNumber(int programNumber);
    void updateDisplay();
    
    Adafruit_SSD1306 display;
    bool isInitialized;
    int lastProgramNumber;
    char programName[MAX_PROGRAM_NAME_LENGTH + 1];
    bool hasProgramName;
    int sdaPin;
    int sclPin;
    uint8_t i2cAddress;
};
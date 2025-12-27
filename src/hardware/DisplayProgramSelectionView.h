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

private:
    static constexpr int SCREEN_WIDTH = 128;
    static constexpr int SCREEN_HEIGHT = 64;
    static constexpr int OLED_RESET = -1;
    
    void initializeDisplay();
    void clearDisplay();
    void displayProgramNumber(int programNumber);
    void showStartupMessage();
    
    Adafruit_SSD1306 display;
    bool isInitialized;
    int lastProgramNumber;
    int sdaPin;
    int sclPin;
    uint8_t i2cAddress;
};
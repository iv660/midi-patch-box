#pragma once

#include "app/MenuLayoutViewInterface.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class DisplayVerticalMenuLayoutView : public MenuLayoutViewInterface
{
public:
    DisplayVerticalMenuLayoutView(int sda_pin = 20, int scl_pin = 21, uint8_t i2c_address = 0x3C);
    ~DisplayVerticalMenuLayoutView();

    DisplayVerticalMenuLayoutView(const DisplayVerticalMenuLayoutView&) = delete;
    DisplayVerticalMenuLayoutView& operator=(const DisplayVerticalMenuLayoutView&) = delete;
    DisplayVerticalMenuLayoutView(DisplayVerticalMenuLayoutView&&) = delete;
    DisplayVerticalMenuLayoutView& operator=(DisplayVerticalMenuLayoutView&&) = delete;

    MenuLayoutViewInterface* setTitle(char* title) override;

private:
    static constexpr int SCREEN_WIDTH = 128;
    static constexpr int SCREEN_HEIGHT = 64;
    static constexpr int OLED_RESET = -1;
    
    void initializeDisplay();
    
    Adafruit_SSD1306 display;
    bool isInitialized;
    int sdaPin;
    int sclPin;
    uint8_t i2cAddress;
};

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

    MenuLayoutViewInterface* displayTitle(char* title) override;
    MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) override;
    MenuLayoutViewInterface* clearItems() override;
    unsigned int getMaxItems() const override;

private:
    static constexpr int SCREEN_WIDTH = 128;
    static constexpr int SCREEN_HEIGHT = 64;
    static constexpr int OLED_RESET = -1;
    static constexpr int TITLE_LINE = 0;
    static constexpr int FIRST_ITEM_LINE = 1;
    static constexpr int TEXT_SIZE = 1;
    static constexpr int LINE_HEIGHT = 12;
    static constexpr int MAX_ITEMS = 4;
    
    void initializeDisplay();
    void redrawScreen();
    int getLineY(int line) const;
    void clearLine(int line);
    void drawTextOnLine(int line, const char* text, bool highlighted);
    void drawHighlightOnLine(int line);
    
    Adafruit_SSD1306 display;
    bool isInitialized;
    int sdaPin;
    int sclPin;
    uint8_t i2cAddress;
};

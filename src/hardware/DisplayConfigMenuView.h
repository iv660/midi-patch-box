#pragma once

#include "app/ConfigMenuViewInterface.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class DisplayConfigMenuView : public ConfigMenuViewInterface
{
public:
    DisplayConfigMenuView(int sda_pin = 20, int scl_pin = 21, uint8_t i2c_address = 0x3C);
    ~DisplayConfigMenuView();

    DisplayConfigMenuView(const DisplayConfigMenuView&) = delete;
    DisplayConfigMenuView& operator=(const DisplayConfigMenuView&) = delete;
    DisplayConfigMenuView(DisplayConfigMenuView&&) = delete;
    DisplayConfigMenuView& operator=(DisplayConfigMenuView&&) = delete;

    ConfigMenuViewInterface* showMenu() override;
    ConfigMenuViewInterface* displayMenuItem(int index, const char* text) override;
    ConfigMenuViewInterface* setSelectedItem(int index) override;

private:
    static constexpr int SCREEN_WIDTH = 128;
    static constexpr int SCREEN_HEIGHT = 64;
    static constexpr int OLED_RESET = -1;
    static constexpr int MAX_MENU_ITEMS = 4;
    static constexpr int MAX_ITEM_TEXT_LENGTH = 16;
    static constexpr int LINE_HEIGHT = 16;
    static constexpr int MENU_START_Y = 8;
    
    void initializeDisplay();
    void updateDisplay();
    
    Adafruit_SSD1306 display;
    bool isInitialized;
    int selectedItemIndex;
    int sdaPin;
    int sclPin;
    uint8_t i2cAddress;
    
    struct MenuItem {
        char text[MAX_ITEM_TEXT_LENGTH + 1];
        bool hasText;
    };
    
    MenuItem menuItems[MAX_MENU_ITEMS];
};
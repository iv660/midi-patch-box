#include "DisplayConfigMenuView.h"
#include <Arduino.h>
#include <cstring>

DisplayConfigMenuView::DisplayConfigMenuView(int sda_pin, int scl_pin, uint8_t i2c_address)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
    , isInitialized(false)
    , selectedItemIndex(0)
    , sdaPin(sda_pin)
    , sclPin(scl_pin)
    , i2cAddress(i2c_address)
{
    // Initialize menu items
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        menuItems[i].text[0] = '\0';
        menuItems[i].hasText = false;
    }
    
    initializeDisplay();
}

DisplayConfigMenuView::~DisplayConfigMenuView()
{
    if (isInitialized) {
        display.clearDisplay();
        display.display();
    }
}

void DisplayConfigMenuView::initializeDisplay()
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

ConfigMenuViewInterface* DisplayConfigMenuView::showMenu()
{
    if (!isInitialized) {
        return this;
    }
    
    updateDisplay();
    return this;
}

ConfigMenuViewInterface* DisplayConfigMenuView::displayMenuItem(int index, const char* text)
{
    if (index < 0 || index >= MAX_MENU_ITEMS) {
        return this;
    }
    
    if (text != nullptr && strlen(text) > 0) {
        strncpy(menuItems[index].text, text, MAX_ITEM_TEXT_LENGTH);
        menuItems[index].text[MAX_ITEM_TEXT_LENGTH] = '\0';
        menuItems[index].hasText = true;
    } else {
        menuItems[index].text[0] = '\0';
        menuItems[index].hasText = false;
    }
    
    updateDisplay();
    return this;
}

ConfigMenuViewInterface* DisplayConfigMenuView::setSelectedItem(int index)
{
    if (index >= 0 && index < MAX_MENU_ITEMS) {
        selectedItemIndex = index;
        updateDisplay();
    }
    
    return this;
}

void DisplayConfigMenuView::updateDisplay()
{
    if (!isInitialized) {
        return;
    }
    
    display.clearDisplay();
    
    // Display title
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Config Menu");
    
    // Display menu items
    for (int i = 0; i < MAX_MENU_ITEMS; i++) {
        if (!menuItems[i].hasText) {
            continue;
        }
        
        int y = MENU_START_Y + (i * LINE_HEIGHT);
        
        // Highlight selected item
        if (i == selectedItemIndex) {
            display.fillRect(0, y - 2, SCREEN_WIDTH, LINE_HEIGHT, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
        } else {
            display.setTextColor(SSD1306_WHITE);
        }
        
        display.setCursor(4, y);
        display.println(menuItems[i].text);
    }
    
    display.display();
}
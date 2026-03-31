#include "DisplayVerticalMenuLayoutView.h"
#include <Arduino.h>
#include <cstring>

DisplayVerticalMenuLayoutView::DisplayVerticalMenuLayoutView(int sda_pin, int scl_pin, uint8_t i2c_address)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
    , isInitialized(false)
    , sdaPin(sda_pin)
    , sclPin(scl_pin)
    , i2cAddress(i2c_address)
{
    initializeDisplay();
}

DisplayVerticalMenuLayoutView::~DisplayVerticalMenuLayoutView()
{
    if (isInitialized) {
        display.clearDisplay();
        display.display();
    }
}

void DisplayVerticalMenuLayoutView::initializeDisplay()
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

MenuLayoutViewInterface* DisplayVerticalMenuLayoutView::setTitle(char* title)
{
    if (!isInitialized || title == nullptr) {
        return this;
    }
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(title);
    display.display();
    
    return this;
}

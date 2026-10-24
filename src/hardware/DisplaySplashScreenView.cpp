#include "DisplaySplashScreenView.h"
#include <Arduino.h>

DisplaySplashScreenView::DisplaySplashScreenView(int sda_pin, int scl_pin, uint8_t i2c_address)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
    , isInitialized(false)
    , sdaPin(sda_pin)
    , sclPin(scl_pin)
    , i2cAddress(i2c_address)
{
    initializeDisplay();
}

DisplaySplashScreenView::~DisplaySplashScreenView()
{
    if (isInitialized) {
        display.clearDisplay();
        display.display();
    }
}

void DisplaySplashScreenView::showMessage()
{
    if (isInitialized) {
        displaySplashMessage();
    }
}

void DisplaySplashScreenView::hide()
{
    if (isInitialized) {
        clearDisplay();
    }
}

void DisplaySplashScreenView::initializeDisplay()
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

void DisplaySplashScreenView::clearDisplay()
{
    display.clearDisplay();
    display.display();
}

void DisplaySplashScreenView::displaySplashMessage()
{
    display.clearDisplay();
    
    // Show "MIDI Patch Box" startup message
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    
    // Center "MIDI" text
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds("MIDI", 0, 0, &x1, &y1, &w, &h);
    int centerX = (SCREEN_WIDTH - w) / 2;
    display.setCursor(centerX, 10);
    display.println("MIDI");
    
    // Center "Patch Box" text
    display.getTextBounds("Patch Box", 0, 0, &x1, &y1, &w, &h);
    centerX = (SCREEN_WIDTH - w) / 2;
    display.setCursor(centerX, 35);
    display.println("Patch Box");
    
    display.display();
}
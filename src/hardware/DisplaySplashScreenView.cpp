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
    
    // Title
    display.setTextSize(2);
    display.setCursor(0, 10);
    display.println("MIDI");
    display.println("Patch Box");
    
    // Version
    display.setTextSize(1);
    display.setCursor(0, 50);
    display.println("v1.0");
    
    display.display();
}
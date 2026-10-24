#pragma once

#include "app/SplashScreenViewInterface.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class DisplayBitmapSplashScreenView : public SplashScreenViewInterface {
public:
    DisplayBitmapSplashScreenView(int sda_pin = 20, int scl_pin = 21, uint8_t i2c_address = 0x3C);
    ~DisplayBitmapSplashScreenView();

    DisplayBitmapSplashScreenView(const DisplayBitmapSplashScreenView&) = delete;
    DisplayBitmapSplashScreenView& operator=(const DisplayBitmapSplashScreenView&) = delete;
    DisplayBitmapSplashScreenView(DisplayBitmapSplashScreenView&&) = delete;
    DisplayBitmapSplashScreenView& operator=(DisplayBitmapSplashScreenView&&) = delete;

    void showMessage() override;
    void hide() override;

private:
    static constexpr int SCREEN_WIDTH = 128;
    static constexpr int SCREEN_HEIGHT = 64;
    static constexpr int OLED_RESET = -1;
    
    void initializeDisplay();
    void clearDisplay();
    void displayBitmapSplash();
    
    Adafruit_SSD1306 display;
    bool isInitialized;
    int sdaPin;
    int sclPin;
    uint8_t i2cAddress;
};
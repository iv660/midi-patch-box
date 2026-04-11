#include "DisplayVerticalMenuLayoutView.h"
#include <Arduino.h>
#include <cstring>

DisplayVerticalMenuLayoutView::DisplayVerticalMenuLayoutView(int sda_pin, int scl_pin, uint8_t i2c_address)
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET),
      isInitialized(false),
      sdaPin(sda_pin),
      sclPin(scl_pin),
      i2cAddress(i2c_address)
{
    initializeDisplay();
}

DisplayVerticalMenuLayoutView::~DisplayVerticalMenuLayoutView() {
}

void DisplayVerticalMenuLayoutView::initializeDisplay() {
    Wire.setSDA(sdaPin);
    Wire.setSCL(sclPin);
    Wire.begin();
    
    if (display.begin(SSD1306_SWITCHCAPVCC, i2cAddress)) {
        isInitialized = true;
        display.clearDisplay();
        display.setTextSize(TEXT_SIZE);
        display.setTextColor(SSD1306_WHITE);
        redrawScreen();
    }
}

void DisplayVerticalMenuLayoutView::redrawScreen() {
    display.display();
}

int DisplayVerticalMenuLayoutView::getLineY(int line) const {
    return line * LINE_HEIGHT;
}

void DisplayVerticalMenuLayoutView::clearLine(int line) {
    int y = getLineY(line);
    display.fillRect(0, y, SCREEN_WIDTH, LINE_HEIGHT, SSD1306_BLACK);
}

void DisplayVerticalMenuLayoutView::drawHighlightOnLine(int line) {
    int y = getLineY(line);
    display.fillRect(0, y, SCREEN_WIDTH, LINE_HEIGHT, SSD1306_WHITE);
}

void DisplayVerticalMenuLayoutView::drawTextOnLine(int line, const char* text, bool highlighted) {
    if (highlighted) {
        drawHighlightOnLine(line);
        display.setTextColor(SSD1306_BLACK);
    } else {
        clearLine(line);
        display.setTextColor(SSD1306_WHITE);
    }
    
    display.setCursor(2, getLineY(line) + 2);
    display.print(text);
}

MenuLayoutViewInterface* DisplayVerticalMenuLayoutView::displayTitle(char* title) {
    drawTextOnLine(TITLE_LINE, title, false);
    redrawScreen();
    return this;
}

MenuLayoutViewInterface* DisplayVerticalMenuLayoutView::displayItem(int index, char* caption, bool highlighted) {
    int line = FIRST_ITEM_LINE + index;
    drawTextOnLine(line, caption, highlighted);
    redrawScreen();
    return this;
}

unsigned int DisplayVerticalMenuLayoutView::getMaxItems() const {
    return MAX_ITEMS;
}

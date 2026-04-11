#pragma once
#include "../../src/app/MenuLayoutViewInterface.h"
#include <string.h>

class MockMenuLayoutView : public MenuLayoutViewInterface {
private:
    char title[16];
    char itemCaptions[10][16];
    bool itemHighlighted[10];
    int itemCount;
    unsigned int maxItems;

public:
    MockMenuLayoutView() : itemCount(0), maxItems(10) {
        title[0] = '\0';
        for (int i = 0; i < 10; i++) {
            itemCaptions[i][0] = '\0';
            itemHighlighted[i] = false;
        }
    }

    void setMaxItems(unsigned int value) {
        maxItems = value;
    }

    MenuLayoutViewInterface* setTitle(char* newTitle) override {
        strncpy(title, newTitle, 16);
        title[15] = '\0';
        return this;
    }

    MenuLayoutViewInterface* addItem(char* caption, bool highlighted) override {
        if (itemCount < 10) {
            strncpy(itemCaptions[itemCount], caption, 16);
            itemCaptions[itemCount][15] = '\0';
            itemHighlighted[itemCount] = highlighted;
            itemCount++;
        }
        return this;
    }

    MenuLayoutViewInterface* draw() override { return this; }
    MenuLayoutViewInterface* resetItems() override { itemCount = 0; return this; }
    unsigned int getMaxItems() const override { return maxItems; }

    // Test helper methods
    const char* getTitle() const { return title; }
    const char* getItemCaption(int index) const {
        return (index >= 0 && index < itemCount) ? itemCaptions[index] : nullptr;
    }
    bool isItemHighlighted(int index) const {
        return (index >= 0 && index < itemCount) ? itemHighlighted[index] : false;
    }
    int getItemCount() const { return itemCount; }
};

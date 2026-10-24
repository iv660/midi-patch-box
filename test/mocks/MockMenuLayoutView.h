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

    MenuLayoutViewInterface* displayTitle(char* newTitle) override {
        strncpy(title, newTitle, 16);
        title[15] = '\0';
        return this;
    }

    MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) override {
        if (index >= 0 && index < 10) {
            strncpy(itemCaptions[index], caption, 16);
            itemCaptions[index][15] = '\0';
            itemHighlighted[index] = highlighted;
            if (index + 1 > itemCount) {
                itemCount = index + 1;
            }
        }
        return this;
    }

    unsigned int getMaxItems() const override { return maxItems; }

    MenuLayoutViewInterface* clearItems() override {
        itemCount = 0;
        for (int i = 0; i < 10; i++) {
            itemCaptions[i][0] = '\0';
            itemHighlighted[i] = false;
        }
        return this;
    }

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

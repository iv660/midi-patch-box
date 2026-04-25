#pragma once
#include "MenuLayoutViewInterface.h"

class SetlistMenuViewDecorator : public MenuLayoutViewInterface {
private:
    MenuLayoutViewInterface* innerView = nullptr;

    int lastHighlightedIndex = -1;
    bool hasLastHighlighted = false;

public:
    SetlistMenuViewDecorator() = default;
    explicit SetlistMenuViewDecorator(MenuLayoutViewInterface* innerView);

    MenuLayoutViewInterface* displayTitle(char* title) override;
    MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) override;
    MenuLayoutViewInterface* clearItems() override;
    unsigned int getMaxItems() const override;

    SetlistMenuViewDecorator* replaceLastHighlightedItem(char* caption);
};


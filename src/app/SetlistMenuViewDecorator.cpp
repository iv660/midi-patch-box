#include "SetlistMenuViewDecorator.h"

SetlistMenuViewDecorator::SetlistMenuViewDecorator(MenuLayoutViewInterface* innerView)
    : innerView(innerView) {
}

MenuLayoutViewInterface* SetlistMenuViewDecorator::displayTitle(char* title) {
    if (!innerView) {
        return this;
    }

    innerView->displayTitle(title);
    return this;
}

MenuLayoutViewInterface* SetlistMenuViewDecorator::displayItem(int index, char* caption, bool highlighted) {
    if (!innerView) {
        return this;
    }

    if (highlighted) {
        lastHighlightedIndex = index;
        hasLastHighlighted = true;
    }

    innerView->displayItem(index, caption, highlighted);
    return this;
}

MenuLayoutViewInterface* SetlistMenuViewDecorator::clearItems() {
    lastHighlightedIndex = -1;
    hasLastHighlighted = false;

    if (!innerView) {
        return this;
    }

    innerView->clearItems();
    return this;
}

unsigned int SetlistMenuViewDecorator::getMaxItems() const {
    return innerView ? innerView->getMaxItems() : 0;
}

SetlistMenuViewDecorator* SetlistMenuViewDecorator::replaceLastHighlightedItem(char* caption) {
    if (!hasLastHighlighted) {
        return this;
    }

    this->displayItem(lastHighlightedIndex, caption, true);
    return this;
}


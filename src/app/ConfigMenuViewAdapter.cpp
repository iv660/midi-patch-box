#include "ConfigMenuViewAdapter.h"
#include <cstring>
#include <algorithm>

// Helper method implementations
void ConfigMenuViewAdapter::ensureViewInitialized() {
    if (wrappedView && !viewInitialized) {
        wrappedView->showMenu();
        viewInitialized = true;
    }
}

bool ConfigMenuViewAdapter::isValidIndex(int index) const {
    return index >= 0 && index < static_cast<int>(maxVisibleItems);
}

void ConfigMenuViewAdapter::updateHighlightState(int index, bool highlighted) {
    if (highlighted) {
        currentHighlightedIndex = index;
        if (wrappedView) {
            wrappedView->setSelectedItem(index);
        }
    }
}

// Constructor
ConfigMenuViewAdapter::ConfigMenuViewAdapter(ConfigMenuViewInterface* view, 
                                             unsigned int maxVisible)
    : wrappedView(view),
      currentHighlightedIndex(-1),
      maxVisibleItems(std::min(maxVisible, static_cast<unsigned int>(MAX_ITEMS))),
      viewInitialized(false) {
    storedTitle[0] = '\0';
    if (maxVisibleItems == 0) {
        maxVisibleItems = 1; // Ensure at least 1 item
    }
}

// MenuLayoutViewInterface implementation
MenuLayoutViewInterface* ConfigMenuViewAdapter::displayTitle(char* title) {
    if (title) {
        // Copy title safely with bounds checking
        strncpy(storedTitle, title, MAX_TITLE_LENGTH);
        storedTitle[MAX_TITLE_LENGTH] = '\0';
    } else {
        storedTitle[0] = '\0';
    }
    return this;
}

MenuLayoutViewInterface* ConfigMenuViewAdapter::displayItem(int index, char* caption, bool highlighted) {
    if (!isValidIndex(index)) {
        return this; // Silently ignore invalid indices
    }
    
    ensureViewInitialized();
    
    if (wrappedView && caption) {
        wrappedView->displayMenuItem(index, caption);
    }
    
    updateHighlightState(index, highlighted);
    
    return this;
}

MenuLayoutViewInterface* ConfigMenuViewAdapter::clearItems() {
    ensureViewInitialized();
    
    // Reset internal state
    currentHighlightedIndex = -1;
    viewInitialized = false; // Will reinitialize on next displayItem
    
    // Reinitialize the view if we have one
    if (wrappedView) {
        wrappedView->showMenu();
        viewInitialized = true;
    }
    
    return this;
}

unsigned int ConfigMenuViewAdapter::getMaxItems() const {
    return maxVisibleItems;
}

// Additional methods
ConfigMenuViewAdapter* ConfigMenuViewAdapter::setWrappedView(ConfigMenuViewInterface* view) {
    wrappedView = view;
    viewInitialized = false; // Need to reinitialize with new view
    return this;
}

ConfigMenuViewInterface* ConfigMenuViewAdapter::getWrappedView() const {
    return wrappedView;
}

const char* ConfigMenuViewAdapter::getStoredTitle() const {
    return storedTitle;
}

int ConfigMenuViewAdapter::getHighlightedIndex() const {
    return currentHighlightedIndex;
}

void ConfigMenuViewAdapter::setMaxVisibleItems(unsigned int maxItems) {
    maxVisibleItems = std::min(maxItems, static_cast<unsigned int>(MAX_ITEMS));
    if (maxVisibleItems == 0) {
        maxVisibleItems = 1;
    }
}

bool ConfigMenuViewAdapter::hasValidView() const {
    return wrappedView != nullptr;
}

bool ConfigMenuViewAdapter::isViewInitialized() const {
    return viewInitialized;
}

ConfigMenuViewAdapter* ConfigMenuViewAdapter::initializeView() {
    if (wrappedView) {
        wrappedView->showMenu();
        viewInitialized = true;
    }
    return this;
}
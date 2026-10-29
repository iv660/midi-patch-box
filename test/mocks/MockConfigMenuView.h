#pragma once

#include "app/ConfigMenuViewInterface.h"

/**
 * @brief Mock implementation of ConfigMenuViewInterface for testing
 */
class MockConfigMenuView : public ConfigMenuViewInterface {
private:
    bool showMenuCalled;
    bool setSelectedItemCalled;
    bool displayMenuItemCalled;
    int lastSelectedItem;
    int lastDisplayMenuItemIndex;
    const char* lastDisplayMenuItemName;
    int displayMenuItemCallCount;
    
public:
    MockConfigMenuView() : 
        showMenuCalled(false),
        setSelectedItemCalled(false),
        displayMenuItemCalled(false),
        lastSelectedItem(-1),
        lastDisplayMenuItemIndex(-1),
        lastDisplayMenuItemName(nullptr),
        displayMenuItemCallCount(0) {}
    
    virtual ~MockConfigMenuView() = default;
    
    // ConfigMenuViewInterface implementation
    ConfigMenuViewInterface* showMenu() override {
        showMenuCalled = true;
        return this;
    }
    
    ConfigMenuViewInterface* setSelectedItem(int itemIndex) override {
        setSelectedItemCalled = true;
        lastSelectedItem = itemIndex;
        return this;
    }
    
    ConfigMenuViewInterface* displayMenuItem(int index, const char* itemName) override {
        displayMenuItemCalled = true;
        lastDisplayMenuItemIndex = index;
        lastDisplayMenuItemName = itemName;
        displayMenuItemCallCount++;
        return this;
    }
    
    // Test helper methods
    bool wasShowMenuCalled() const { return showMenuCalled; }
    bool wasSetSelectedItemCalled() const { return setSelectedItemCalled; }
    bool wasDisplayMenuItemCalled() const { return displayMenuItemCalled; }
    int getLastSelectedItem() const { return lastSelectedItem; }
    int getLastDisplayMenuItemIndex() const { return lastDisplayMenuItemIndex; }
    const char* getLastDisplayMenuItemName() const { return lastDisplayMenuItemName; }
    int getDisplayMenuItemCallCount() const { return displayMenuItemCallCount; }
    
    void reset() {
        showMenuCalled = false;
        setSelectedItemCalled = false;
        displayMenuItemCalled = false;
        lastSelectedItem = -1;
        lastDisplayMenuItemIndex = -1;
        lastDisplayMenuItemName = nullptr;
        displayMenuItemCallCount = 0;
    }
    
    // Prevent copying
    MockConfigMenuView(const MockConfigMenuView&) = delete;
    MockConfigMenuView& operator=(const MockConfigMenuView&) = delete;
    
    // Allow moving
    MockConfigMenuView(MockConfigMenuView&&) = default;
    MockConfigMenuView& operator=(MockConfigMenuView&&) = default;
};
#pragma once

class ConfigMenuViewInterface {
public:
    virtual ~ConfigMenuViewInterface() = default;
    virtual ConfigMenuViewInterface* showMenu() = 0;
    virtual ConfigMenuViewInterface* setSelectedItem(int itemIndex) = 0;
    virtual ConfigMenuViewInterface* displayMenuItem(int itemIndex, const char* itemName) = 0;
};
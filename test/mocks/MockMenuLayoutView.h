#pragma once
#include "../../src/app/MenuLayoutViewInterface.h"
#include <string.h>

class MockMenuLayoutView : public MenuLayoutViewInterface {
private:
    char title[16];

public:
    MenuLayoutViewInterface* setTitle(char* newTitle) override {
        strncpy(title, newTitle, 16);
        title[15] = '\0';
        return this;
    }

    // Test helper methods
    const char* getTitle() const { return title; }
};

#pragma once

class MenuLayoutViewInterface {
public:
    virtual MenuLayoutViewInterface* setTitle(char* title) = 0;
    virtual MenuLayoutViewInterface* addItem(char* caption, bool highlighted) = 0;
    virtual MenuLayoutViewInterface* draw() = 0;
    virtual MenuLayoutViewInterface* resetItems() = 0;
    virtual unsigned int getMaxItems() const = 0;
    virtual ~MenuLayoutViewInterface() = default;
};

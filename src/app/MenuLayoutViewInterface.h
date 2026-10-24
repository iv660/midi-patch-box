#pragma once

class MenuLayoutViewInterface {
public:
    virtual MenuLayoutViewInterface* displayTitle(char* title) = 0;
    virtual MenuLayoutViewInterface* displayItem(int index, char* caption, bool highlighted) = 0;
    virtual MenuLayoutViewInterface* clearItems() = 0;
    virtual unsigned int getMaxItems() const = 0;
    virtual ~MenuLayoutViewInterface() = default;
};

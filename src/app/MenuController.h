#pragma once

#include "MenuLayoutViewInterface.h"
#include "MenuControllerInterface.h"
#include "DiContainerInterface.h"

class MenuController: public MenuControllerInterface {
public:
    MenuController() = default;
    
    explicit MenuController(DiContainerInterface* container) : diContainer(container) {
    }
    
    void setTitle(char* title) override;

private:
    DiContainerInterface* diContainer = nullptr;
    
    MenuLayoutViewInterface* getView() const {
        return diContainer ? diContainer->getSetlistMenuLayoutView() : nullptr;
    }
    
    bool hasView() const {
        return getView() != nullptr;
    }
};

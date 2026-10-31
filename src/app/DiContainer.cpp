#include "DiContainer.h"

DiContainer::DiContainer() : setlistManager(nullptr), ownsSetlistManager(false) {
}

DiContainer::~DiContainer() {
    if (ownsSetlistManager) {
        delete setlistManager;
    }
}

SetlistManager* DiContainer::getSetlistManager() const {
    if (setlistManager == nullptr) {
        // Lazy initialization - create on first access
        const_cast<DiContainer*>(this)->setlistManager = new SetlistManager();
        const_cast<DiContainer*>(this)->ownsSetlistManager = true;
    }
    return setlistManager;
}

#include "DiContainer.h"

DiContainer::DiContainer() : setlistManager(nullptr) {
}

DiContainer::~DiContainer() {
    delete setlistManager;
}

SetlistManager* DiContainer::getSetlistManager() const {
    if (setlistManager == nullptr) {
        // Lazy initialization - create on first access
        const_cast<DiContainer*>(this)->setlistManager = new SetlistManager();
    }
    return setlistManager;
}

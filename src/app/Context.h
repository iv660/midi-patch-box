#pragma once

#include "SetlistManager.h"

struct Context {
    const int* programs;
    int programsCount;
    
    Context() : programs(nullptr), programsCount(0) {}
    
    void setSetlistManager(SetlistManager* manager) {
        programs = manager->getPrograms();
        programsCount = manager->getProgramCount();
    }
};

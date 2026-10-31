#include "SetlistManager.h"

SetlistManager::SetlistManager() : count(3) {
    programs[0] = 0;
    programs[1] = 41;
    programs[2] = 112;
}

void SetlistManager::updateProgram(int index, int programNumber) {
    // Bounds checking - silently ignore invalid updates
    if (index < 0 || index >= count) {
        return;
    }
    programs[index] = programNumber;
}

int SetlistManager::getProgram(int index) const {
    return programs[index];
}

int SetlistManager::getProgramCount() const {
    return count;
}

const int* SetlistManager::getPrograms() const {
    return programs;
}

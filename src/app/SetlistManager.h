#pragma once

class SetlistManager {
public:
    SetlistManager();
    
    void updateProgram(int index, int programNumber);
    int getProgram(int index) const;
    int getProgramCount() const;
    const int* getPrograms() const;
    
private:
    static constexpr int CAPACITY = 16;
    int programs[CAPACITY];
    int count;
};

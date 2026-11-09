#pragma once

#include <cstdint>
#include <string>

using namespace std;

class Memory {
private:
    static const int MEMORY_SIZE = 256;
    uint8_t memory[MEMORY_SIZE];

public:
    Memory();
    void SetMemory(uint8_t address, uint8_t value);
    uint8_t GetMemory(uint8_t address) const;
    void ClearMemory();
    string displayMatrix() const;
};
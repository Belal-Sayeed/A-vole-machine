#pragma once
#include <cstdint>
class Memory
{
    public:
    static const int MEMORY_SIZE = 256;
    Memory();
    void SetMemory(uint8_t address, uint8_t value);
    uint8_t GetMemory(uint8_t address) const;
    void ClearMemory();
    private:
    uint8_t memory[MEMORY_SIZE];
};
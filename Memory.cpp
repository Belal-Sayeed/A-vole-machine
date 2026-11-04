#include "Memory.h"

Memory::Memory() 
{
    ClearMemory();
}

void Memory::ClearMemory()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = 0;
    }
}

void Memory::SetMemory(uint8_t address, uint8_t value)
{
    memory[address] = value;
}

uint8_t Memory::GetMemory(uint8_t address) const
{
    return memory[address];
}
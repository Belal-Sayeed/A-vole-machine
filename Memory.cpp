#include "Memory.h"
#include <sstream>
#include <iomanip>

using namespace std;

Memory::Memory()
{
    ClearMemory();
}

void Memory::ClearMemory()
{
    for (int i = 0; i < MEMORY_SIZE; i++) {
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

string Memory::displayMatrix() const
{
    stringstream ss;
    ss << "     ";
    for (int col = 0; col < 16; col++) {
        ss << hex << uppercase << setw(2) << setfill('0') << col << " ";
    }
    ss << "\n----------------------------------------------------\n";

    for (int row = 0; row < 16; row++) {
        ss << hex << uppercase << setw(2) << setfill('0') << (row * 16) << " | ";
        for (int col = 0; col < 16; col++) {
            int index = (row * 16) + col;
            ss << hex << uppercase << setw(2) << setfill('0') << (int)memory[index] << " ";
        }
        ss << "\n";
    }
    return ss.str();
}
#pragma once
#include <cstdint>
using namespace std;
class Memory 
{
    private:
    uint8_t memory[256];
    public:
    Memory()
    {
        for (int i = 0; i < 256; i++)
        {
            memory[i] = 0;
        }
    }
    void SetMemory();
    



};
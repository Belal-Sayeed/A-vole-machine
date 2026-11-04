#include "Register.h"

Register::Register() 
{
    ClearRegisters();
}

void Register::ClearRegisters()
{
    for (int i = 0; i < REGISTER_SIZE; i++)
    {
        registers[i] = 0;
    }
}

bool Register::SetRegister(uint8_t index, uint8_t value)
{
    if (index >= REGISTER_SIZE) 
    {
        return false;
    }
    registers[index] = value;
    return true;
}

uint8_t Register::GetRegister(uint8_t index) const
{
    if (index >= REGISTER_SIZE) 
    {
        return 0;
    }
    return registers[index];
}
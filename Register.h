#pragma once
#include <cstdint>
class Register
{
    public:
    static const int REGISTER_SIZE = 16;
    Register();
    bool SetRegister(uint8_t index, uint8_t value);
    uint8_t GetRegister(uint8_t index) const;
    void ClearRegisters();
    private:
    uint8_t registers[REGISTER_SIZE];
};
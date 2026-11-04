#pragma once
#include <cstdint>
using namespace std;
class Instruction
{
    public:
    void ClearInstruction();
    void SetInstruction(uint16_t value);
    uint4_t Get_Opcode() const;

    private:
    uint16_t instruction;
};
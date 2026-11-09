#include "Instruction.h"

Instruction::Instruction(uint16_t order)
{
    instruction = order;
}

uint8_t Instruction::getOpcode() const
{
    return (instruction >> 12);
}

uint8_t Instruction::getR() const
{
    return (instruction >> 8) & 0x0F;
}

uint8_t Instruction::getS() const
{
    return (instruction >> 4) & 0x0F;
}

uint8_t Instruction::getT() const
{
    return instruction & 0x0F;
}

uint8_t Instruction::getXY() const
{
    return instruction & 0xFF;
}

uint8_t Instruction::getX() const
{
    return instruction & 0x0F;
}

bool Instruction::hasvalidFormat() const
{
    uint8_t op = getOpcode();

    switch (op) {
        case 0x1:
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
            return true;
        default:
            return false;
    }
}
#include "Alu.h"

uint8_t ALU::addTwosComplement(uint8_t a, uint8_t b) const
{
    return a + b;
}

uint8_t ALU::addFloat(uint8_t a, uint8_t b) const
{
    return 0; 
}

uint8_t ALU::bitwiseOr(uint8_t a, uint8_t b) const
{
    return a | b;
}

uint8_t ALU::bitwiseAnd(uint8_t a, uint8_t b) const
{
    return a & b;
}

uint8_t ALU::bitwiseXor(uint8_t a, uint8_t b) const
{
    return a ^ b;
}

uint8_t ALU::rotateRight(uint8_t value, uint8_t times) const
{
    times = times % 8;
    return (value >> times) | (value << (8 - times));
}
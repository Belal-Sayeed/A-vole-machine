#pragma once
#include <cstdint>

class Instruction
{
    public:
    Instruction(uint16_t order);
    uint8_t getOpcode() const;
    uint8_t getR() const;
    uint8_t getS() const;
    uint8_t getT() const;
    uint8_t getXY() const;
    uint8_t getX() const;
    bool hasvalidFormat() const;

    private:
    uint16_t instruction;
};
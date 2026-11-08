#pragma once
#include <cstdint>

class ALU {
public:
    uint8_t addTwosComplement(uint8_t a, uint8_t b) const;
    uint8_t addFloat(uint8_t a, uint8_t b) const;
    uint8_t bitwiseOr(uint8_t a, uint8_t b) const;
    uint8_t bitwiseAnd(uint8_t a, uint8_t b) const;
    uint8_t bitwiseXor(uint8_t a, uint8_t b) const;
    uint8_t rotateRight(uint8_t value, uint8_t times) const;
};
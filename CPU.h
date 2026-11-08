#pragma once

#include <cstdint>
#include <string>
#include "Instruction.h"
#include "Register.h"
#include "Memory.h"
#include "Alu.h"
#include "Screen.h"

class CPU {
private:
    uint8_t pc;
    uint16_t ir;
    bool halted;
    std::string errorReason;
    Register registers;
    ALU alu;
    Memory memory;
    Screen screen;

public:
    CPU();
    void reset(uint8_t startAddress);
    void clearMachine();
    bool step();
    bool isHalted() const;
    std::string getErrorReason() const;
    uint8_t getPC() const;
    uint16_t getIR() const;
    uint8_t getRegister(int index) const;
    void setRegister(int index, uint8_t value);
    uint16_t fetch();
    void execute(const Instruction& instruction);

    Memory& getMemory();
    Screen& getScreen();
};
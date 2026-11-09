#pragma once

#include <string>
#include <cstdint>
#include "CPU.h"
#include "Memory.h"
#include "Screen.h"
#include "ProgramLoader.h"

using namespace std;

class VoleSimulator {
private:
    Memory memory;
    Screen screen;
    ProgramLoader loader;
    CPU cpu;

public:
    VoleSimulator();
    bool loadProgram(const string& filename, uint8_t startAddress);
    void runAll();
    bool step();
    void editRegister(int index, uint8_t value);
    void editMemory(uint8_t address, uint8_t value);
    bool isHalted() const;
    string getLastError() const;
    uint8_t getPC() const;
    uint16_t getIR() const;
    uint8_t getRegister(int index) const;
    const Memory& getMemory() const;
    const Screen& getScreen() const;
};
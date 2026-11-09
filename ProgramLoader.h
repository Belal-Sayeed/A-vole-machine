#pragma once

#include <string>
#include "Memory.h"

class ProgramLoader {
private:
    std::string lastError;

public:
    ProgramLoader();
    bool load(const std::string& filename, uint8_t startAddress, Memory& memory);
    bool isValidStartAddress(uint8_t address) const;
    uint16_t parseInstructionLine(const std::string& line) const;
    bool validateProgramInstruction(uint16_t raw) const;
    std::string getLastError() const;
};
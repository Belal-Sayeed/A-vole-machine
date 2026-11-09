#include "ProgramLoader.h"
#include "Instruction.h"
#include <fstream>
#include <sstream>

using namespace std;

ProgramLoader::ProgramLoader()
{
    lastError = "";
}

bool ProgramLoader::load(const string& filename, uint8_t startAddress, Memory& memory)
{
    ifstream file(filename);
    if (!file.is_open()) {
        lastError = "Could not open file: " + filename;
        return false;
    }

    if (!isValidStartAddress(startAddress)) {
        lastError = "Invalid start address.";
        return false;
    }

    string line;
    uint8_t currentAddress = startAddress;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        uint16_t rawInstruction = parseInstructionLine(line);
        if (!validateProgramInstruction(rawInstruction)) {
            lastError = "Invalid instruction or format in line: " + line;
            return false;
        }

        if (currentAddress > 0xFE) {
            lastError = "Program exceeds memory bounds.";
            return false;
        }

        uint8_t highByte = (rawInstruction >> 8) & 0xFF;
        uint8_t lowByte = rawInstruction & 0xFF;

        memory.SetMemory(currentAddress, highByte);
        memory.SetMemory(currentAddress + 1, lowByte);

        currentAddress += 2;
    }

    file.close();
    return true;
}

bool ProgramLoader::isValidStartAddress(uint8_t address) const
{
    return (address % 2 == 0) && (address <= 0xFE);
}

uint16_t ProgramLoader::parseInstructionLine(const string& line) const
{
    stringstream ss(line);
    uint32_t val;
    ss >> hex >> val;
    return static_cast<uint16_t>(val);
}

bool ProgramLoader::validateProgramInstruction(uint16_t raw) const
{
    Instruction instr(raw);
    return instr.hasvalidFormat();
}

string ProgramLoader::getLastError() const
{
    return lastError;
}
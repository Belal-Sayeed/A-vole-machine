#include "ProgramLoader.h"
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

ProgramLoader::ProgramLoader() : lastError("")
{
}

bool ProgramLoader::load(const string& filename, uint8_t startAddress, Memory& memory)
{
    lastError = "";
    ifstream file(filename);
    if (!file.is_open()) {
        lastError = "Could not open file: " + filename;
        return false;
    }

    string line;
    uint8_t currentAddress = startAddress;

    while (getline(file, line)) {
        size_t start = line.find_first_not_of(" \t\r\n");
        if (start == string::npos) {
            continue;
        }
        
        if (line[start] == ';') {
            continue;
        }

        string instStr = "";
        for (size_t i = start; i < line.length() && !isspace(line[i]); i++) {
            instStr += line[i];
        }

        if (instStr.length() != 4) {
            lastError = "Invalid instruction format: " + instStr;
            return false;
        }

        uint32_t fullInst = stoi(instStr, nullptr, 16);
        uint8_t byte1 = (fullInst >> 8) & 0xFF;
        uint8_t byte2 = fullInst & 0xFF;

        if (currentAddress + 1 >= 256) {
            lastError = "Program exceeds memory size limit.";
            return false;
        }

        memory.SetMemory(currentAddress, byte1);
        memory.SetMemory(currentAddress + 1, byte2);
        currentAddress += 2;
    }

    file.close();
    return true;
}

string ProgramLoader::getLastError() const
{
    return lastError;
}
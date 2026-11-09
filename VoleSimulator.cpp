#include "VoleSimulator.h"

using namespace std;

VoleSimulator::VoleSimulator() : cpu(memory, screen)
{
}

bool VoleSimulator::loadProgram(const string& filename, uint8_t startAddress)
{
    cpu.clearMachine();
    if (!loader.load(filename, startAddress, memory)) {
        return false;
    }
    cpu.reset(startAddress);
    return true;
}

void VoleSimulator::runAll()
{
    while (!cpu.isHalted()) {
        cpu.step();
    }
}

bool VoleSimulator::step()
{
    return cpu.step();
}

void VoleSimulator::editRegister(int index, uint8_t value)
{
    cpu.setRegister(index, value);
}

void VoleSimulator::editMemory(uint8_t address, uint8_t value)
{
    memory.SetMemory(address, value);
}

bool VoleSimulator::isHalted() const
{
    return cpu.isHalted();
}

string VoleSimulator::getLastError() const
{
    if (!cpu.getErrorReason().empty()) {
        return cpu.getErrorReason();
    }
    return loader.getLastError();
}

uint8_t VoleSimulator::getPC() const
{
    return cpu.getPC();
}

uint16_t VoleSimulator::getIR() const
{
    return cpu.getIR();
}

uint8_t VoleSimulator::getRegister(int index) const
{
    return cpu.getRegister(index);
}

const Memory& VoleSimulator::getMemory() const
{
    return memory;
}

const Screen& VoleSimulator::getScreen() const
{
    return screen;
}
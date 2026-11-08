#include "CPU.h"

CPU::CPU()
{
    clearMachine();
    reset(0x00);
}

void CPU::reset(uint8_t startAddress)
{
    pc = startAddress;
    ir = 0;
    halted = false;
    errorReason = "";
}

void CPU::clearMachine()
{
    registers.ClearRegisters();
    memory.ClearMemory();
    screen.ClearScreen();
}

bool CPU::step()
{
    if (halted) return false;

    if (pc > 0xFF) {
        halted = true;
        errorReason = "Program counter out of bounds.";
        return false;
    }

    ir = fetch();
    Instruction instr(ir);

    if (!instr.hasvalidFormat()) {
        halted = true;
        errorReason = "Invalid instruction format.";
        return false;
    }

    execute(instr);
    return !halted;
}

bool CPU::isHalted() const
{
    return halted;
}

std::string CPU::getErrorReason() const
{
    return errorReason;
}

uint8_t CPU::getPC() const
{
    return pc;
}

uint16_t CPU::getIR() const
{
    return ir;
}

uint8_t CPU::getRegister(int index) const
{
    return registers.GetRegister(index);
}

void CPU::setRegister(int index, uint8_t value)
{
    registers.SetRegister(index, value);
}

uint16_t CPU::fetch()
{
    uint8_t highByte = memory.GetMemory(pc);
    uint8_t lowByte = 0;

    if (pc == 0xFF) {
        halted = true;
        errorReason = "Instruction truncated at the end of memory.";
        pc += 1;
        return static_cast<uint16_t>(highByte) << 8;
    }

    lowByte = memory.GetMemory(pc + 1);
    pc += 2;
    return (static_cast<uint16_t>(highByte) << 8) | lowByte;
}

void CPU::execute(const Instruction& instruction)
{
    uint8_t op = instruction.getOpcode();
    uint8_t r = instruction.getR();
    uint8_t s = instruction.getS();
    uint8_t t = instruction.getT();
    uint8_t xy = instruction.getXY();

    switch (op) {
        case 0x1:
            setRegister(r, memory.GetMemory(xy));
            break;

        case 0x2:
            setRegister(r, xy);
            break;

        case 0x3:
            if (xy == 0xFF) {
                screen.setscreen(getRegister(r));
            } else {
                memory.SetMemory(xy, getRegister(r));
            }
            break;

        case 0x4:
            setRegister(t, getRegister(s));
            break;

        case 0x5:
            setRegister(r, alu.addTwosComplement(getRegister(s), getRegister(t)));
            break;

        case 0x6:
            setRegister(r, alu.addFloat(getRegister(s), getRegister(t)));
            break;

        case 0x7:
            setRegister(r, alu.bitwiseOr(getRegister(s), getRegister(t)));
            break;

        case 0x8:
            setRegister(r, alu.bitwiseAnd(getRegister(s), getRegister(t)));
            break;

        case 0x9:
            setRegister(r, alu.bitwiseXor(getRegister(s), getRegister(t)));
            break;

        case 0xA:
            setRegister(r, alu.rotateRight(getRegister(r), t));
            break;

        case 0xB:
            if (getRegister(r) == getRegister(0)) {
                pc = xy;
            }
            break;

        case 0xC:
            halted = true;
            errorReason = "Normal HALT execution.";
            break;
    }
}

Memory& CPU::getMemory()
{
    return memory;
}

Screen& CPU::getScreen()
{
    return screen;
}
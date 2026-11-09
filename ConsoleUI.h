#pragma once

#include "VoleSimulator.h"

using namespace std;

class ConsoleUI {
private:
    VoleSimulator simulator;

    void showMenu() const;
    void loadProgram();
    void runContinuously();
    void runOneStep();
    void editRegister();
    void editMemory();
    void displayMachineState() const;
    void waitForEnter() const;

public:
    ConsoleUI();
    void run();
};
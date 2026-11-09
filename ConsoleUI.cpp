#include "ConsoleUI.h"
#include <iostream>
#include <iomanip>

using namespace std;

ConsoleUI::ConsoleUI()
{
}

void ConsoleUI::run()
{
    int choice = 0;
    do {
        showMenu();
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            choice = 0;
        }

        switch (choice) {
            case 1:
                loadProgram();
                break;
            case 2:
                runContinuously();
                break;
            case 3:
                runOneStep();
                break;
            case 4:
                displayMachineState();
                break;
            case 5:
                editRegister();
                break;
            case 6:
                editMemory();
                break;
            case 7:
                cout << "Exiting simulator. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                waitForEnter();
                break;
        }
    } while (choice != 7);
}

void ConsoleUI::showMenu() const
{
    cout << "\n===============================" << endl;
    cout << "      VOLE MACHINE SIMULATOR   " << endl;
    cout << "===============================" << endl;
    cout << "1. Load Program from File" << endl;
    cout << "2. Run Program at Once (Continuous)" << endl;
    cout << "3. Run Program Step by Step" << endl;
    cout << "4. Display Machine State & Memory Matrix" << endl;
    cout << "5. Edit Register" << endl;
    cout << "6. Edit Memory" << endl;
    cout << "7. Exit" << endl;
    cout << "-------------------------------" << endl;
}

void ConsoleUI::loadProgram()
{
    string filename;
    int startAddrHex;
    cout << "Enter filename (e.g., Program 1.txt): ";
    cin >> filename;
    cout << "Enter start address in hex (even address like 0): ";
    cin >> hex >> startAddrHex;
    cin.clear();
    cin.ignore(10000, '\n');

    if (simulator.loadProgram(filename, static_cast<uint8_t>(startAddrHex))) {
        cout << "\nProgram loaded successfully!" << endl;
        displayMachineState();
    } else {
        cout << "Error loading program: " << simulator.getLastError() << endl;
    }
    waitForEnter();
}

void ConsoleUI::runContinuously()
{
    if (simulator.isHalted()) {
        cout << "Machine is halted or no valid program loaded." << endl;
        waitForEnter();
        return;
    }

    simulator.runAll();
    cout << "\n--- PROGRAM FINISHED (RUN AT ONCE) ---" << endl;
    if (!simulator.getLastError().empty()) {
        cout << "Status/Error: " << simulator.getLastError() << endl;
    }
    displayMachineState();
    
    char choice;
    cout << "Would you like to load another program? (y/n): ";
    cin >> choice;
    cin.clear();
    cin.ignore(10000, '\n');
    if (choice == 'y' || choice == 'Y') {
        loadProgram();
    }
}

void ConsoleUI::runOneStep()
{
    if (simulator.isHalted()) {
        cout << "Machine is already halted." << endl;
        waitForEnter();
        return;
    }

    bool active = simulator.step();
    cout << "\n--- STEP EXECUTED ---" << endl;
    displayMachineState();

    if (!active || simulator.isHalted()) {
        cout << "Program finished / Machine halted. Reason: " << simulator.getLastError() << endl;
        char choice;
        cout << "Would you like to load another program? (y/n): ";
        cin >> choice;
        cin.clear();
        cin.ignore(10000, '\n');
        if (choice == 'y' || choice == 'Y') {
            loadProgram();
        }
    } else {
        waitForEnter();
        runOneStep();
    }
}

void ConsoleUI::displayMachineState() const
{
    cout << "\n================ MACHINE STATE ================" << endl;
    cout << "PC: 0x" << hex << uppercase << setw(2) << setfill('0') << (int)simulator.getPC() << dec << endl;
    cout << "IR: 0x" << hex << uppercase << setw(4) << setfill('0') << simulator.getIR() << dec << endl;
    cout << "Halted: " << (simulator.isHalted() ? "Yes" : "No") << endl;

    cout << "\n--- Registers ---" << endl;
    for (int i = 0; i < 16; i++) {
        cout << "R" << hex << uppercase << i << ": 0x" << setw(2) << setfill('0') << (int)simulator.getRegister(i) 
             << " (" << dec << (int)simulator.getRegister(i) << ")  ";
        if (i % 4 == 3) cout << endl;
    }
    cout << dec;

    cout << "\n--- Memory Matrix (16x16) ---" << endl;
    cout << simulator.getMemory().displayMatrix() << endl;
}

void ConsoleUI::editRegister()
{
    int index, val;
    cout << "Enter register index (0-15 in hex): ";
    cin >> hex >> index;
    cout << "Enter new value (0-255 in hex): ";
    cin >> val;
    cin.clear();
    cin.ignore(10000, '\n');

    if (index >= 0 && index < 16) {
        simulator.editRegister(index, static_cast<uint8_t>(val));
        cout << "Register updated successfully." << endl;
    } else {
        cout << "Invalid register index." << endl;
    }
    waitForEnter();
}

void ConsoleUI::editMemory()
{
    int addr, val;
    cout << "Enter memory address (hex): ";
    cin >> hex >> addr;
    cout << "Enter value (hex): ";
    cin >> val;
    cin.clear();
    cin.ignore(10000, '\n');

    if (addr >= 0 && addr < 256) {
        simulator.editMemory(static_cast<uint8_t>(addr), static_cast<uint8_t>(val));
        cout << "Memory updated successfully." << endl;
    } else {
        cout << "Invalid memory address." << endl;
    }
    waitForEnter();
}

void ConsoleUI::waitForEnter() const
{
    cout << "\nPress Enter to continue...";
    cin.get();
}
#include "Screen.h"
using namespace std;
void Screen::ClearScreen()
{
    output.clear();
}

void Screen::setscreen(uint8_t value)
{
    output.push_back(value);
}

const vector<uint8_t>& Screen::getscreen() const
{
    return output;
}
#pragma once
#include <vector>
#include <cstdint>

using namespace std;

class Screen
{
    public:
    void ClearScreen();
    void setscreen(uint8_t value);
    const vector<uint8_t>& getscreen() const;

    private:
    vector<uint8_t> output;
};
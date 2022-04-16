#include "TimeDisplay.h"

#include <Arduino.h>

namespace timeDisplay {

// TODO: use bits instead of bools. Research must be made
bool screenOn = true;
bool editMode = false;
bool clkDiv = true;

int lastUpdate = 0;  // time in ms
int row = 0;         // current row to draw
int previousRow = 0;

void setup() {
    // prepare Shift Registers
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
}

void drawNumbers(const uint8_t* numberArr) {
    if (previousRow == row) {
        return;
    }
    // TODO: there must be a way to upgrade the if/else
    if (row != DISPLAY_DIGITS - 1) {
        drawNumber(numberArr[row], row);
    } else {  // draw clockDivider
        drawNumber(10, row);
    }
}

void drawNumber(const uint8_t number, const uint8_t digit) {
    uint16_t byteValue = getDigit(number) + getDigitPosition(digit);
    digitalWrite(STCP, LOW);  // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA

    shiftOut(DS, SHCP, LSBFIRST, byteValue);
    shiftOut(DS, SHCP, LSBFIRST, byteValue >> 8);  // Using a daisy chained 2x8 bit 74HC595N requires a shift right

    digitalWrite(STCP, HIGH);  // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
}

uint16_t getDigit(const uint8_t num) {
    switch (num) {
        case 0:
            return ZERO;
        case 1:
            return ONE;
        case 2:
            return TWO;
        case 3:
            return THREE;
        case 4:
            return FOUR;
        case 5:
            return FIVE;
        case 6:
            return SIX;
        case 7:
            return SEVEN;
        case 8:
            return EIGHT;
        case 9:
            return NINE;
        case 10:
            return CLOCK_DIVIDER;
        default:
            return 0;
    }
}

uint16_t getDigitPosition(const uint8_t digit) {
    if (!screenOn) {
        return 0;
    }

    switch (digit) {
        case 0:
            return D1;
        case 1:
            return D2;
        case 2:
            return D3;
        case 3:
            return D4;
        case 4:
            return L1;
        default:
            return D1;
    }
}

void update(int currentTime) {
    uint8_t moduloDiv = DISPLAY_DIGITS;
    if (!clkDiv) {
        moduloDiv--;
    }
    if (currentTime - lastUpdate >= UPDATE_TIME) {
        previousRow = row;
        row = (row + 1) % moduloDiv;
        lastUpdate = currentTime;
    }
}

inline void toggleEditMode() { editMode = !editMode; }

inline void toggleScreenPower() { screenOn = !screenOn; }

inline void toggleClockDivider() { clkDiv = !clkDiv; }

};  // namespace timeDisplay

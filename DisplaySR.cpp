#include "DisplaySR.h"

#include <Arduino.h>

namespace timeDisplay {

// TODO: use bits instead of bools. Research must be made
bool screenOn = true;
bool editMode = false;
bool clkDiv = true;

void setup() {
    // prepare Shift Registers
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
}

void drawNumbers(const uint8_t* numberArr, uint8_t size, const bool clkDiv) {
    if (size < 0) {
        // size out of bounds
        return;
    } else if (size > 4) {
        size = 4;
    }

    for (int i = 0; i < size; i++) {
        drawNumber(numberArr[i], i);
    }
    if (clkDiv) {
        drawNumber(10, 4);  // 10 is the value representing the clock divider
    }
}

void drawNumber(const uint8_t number, const uint8_t digit) {
    // TODO: make verification  if previous call was already turn off so it stops writing in shift registers and saving energy

    uint16_t byteValue = getDigit(number) + getDigitPosition(digit);
    // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA
    digitalWrite(STCP, LOW);
    // shiftOut(DS, SHCP, MSBFIRST, D1);
    shiftOut(DS, SHCP, LSBFIRST, byteValue);
    shiftOut(DS, SHCP, LSBFIRST, byteValue >> 8);

    // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
    digitalWrite(STCP, HIGH);
    // TODO: change delay to fps
    delay(2.5);
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
    if (digit < 0 || digit > 4 || !screenOn) {
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
    }
}

inline void toggleEditMode() { editMode = !editMode; }

inline void toggleScreenPower() { screenOn = !screenOn; }

inline void toggleClockDivider() { clkDiv = !clkDiv; }
};  // namespace timeDisplay

#include "DisplaySR.h"

#include <Arduino.h>

namespace timeDisplay {
const uint8_t DS = 8;
const uint8_t STCP = 9;
const uint8_t SHCP = 10;
// SEGMENT SELECTOR - HIGH IS OFF
const uint16_t ZERO = 0b0000000000010000;
const uint16_t ONE = 0b0100100001110000;
const uint16_t TWO = 0b0001000000100000;
const uint16_t THREE = 0b0000000001100000;
const uint16_t FOUR = 0b0100100001000000;
const uint16_t FIVE = 0b0010000001000000;
const uint16_t SIX = 0b0010000000000000;
const uint16_t SEVEN = 0b0000100001110000;
const uint16_t EIGHT = 0b0000000000000000;
const uint16_t NINE = 0b0000000001000000;
const uint16_t CLOCK_DIVIDER = 0b0001000000000000;

// DIGIT POSITION SELECTOR - LOW IS OFF
const uint16_t D1 = 0b0000001000000000;
const uint16_t D2 = 0b0000000000001000;
const uint16_t D3 = 0b0000000000000100;
const uint16_t D4 = 0b0000000000000010;
const uint16_t L1 = 0b0000010000000000;

bool screenOn = true;
bool editMode = false;
bool clkDiv = true;

};  // namespace timeDisplay

void timeDisplay::setup() {
    // prepare Shift Registers
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
}

void timeDisplay::drawNumbers(const uint8_t* numberArr, uint8_t size, const bool clkDiv) {
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

void timeDisplay::drawNumber(const uint8_t number, const uint8_t digit) {
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

uint16_t timeDisplay::getDigit(const uint8_t num) {
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

uint16_t timeDisplay::getDigitPosition(const uint8_t digit) {
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

inline void timeDisplay::toggleEditMode() { editMode = !editMode; }

inline void timeDisplay::toggleScreenPower() { screenOn = !screenOn; }

inline void timeDisplay::toggleClockDivider() { clkDiv = !clkDiv; }
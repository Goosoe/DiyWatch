#include "SevenSegment.h"

#include <Arduino.h>
#include "../Util.h"
namespace timeDisplay {

const uint8_t DS = 8;
const uint8_t STCP = 9;
const uint8_t SHCP = 10;
const uint8_t BLOCK = 5;
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

const uint16_t REFRESH = 260;  // nr of refreshes per sec
const float UPDATE_TIME = 1000 / REFRESH;
const uint16_t BLINK_TIMER = 600;
const uint8_t DISPLAY_DIGITS = 5;  // The 5th digit is the clock separator

uint32_t lastUpdate = 0;  // time in ms
uint32_t lastBlink = 0;   // time in ms

uint8_t row = 0;  // current row to draw
uint8_t previousRow = 0;
uint16_t previousByteValue = 0;

uint8_t editableDigits = 0;  // 0 = hours digits, 1 = minutes digits TODO: Switch this to Screen Controller
bool screenOn = true;
bool clkDiv = true;

bool blink = false;

void setup() {
    // prepare Shift Registers
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
    pinMode(BLOCK, OUTPUT);
}

void drawNumbers(const uint8_t* numberArr) {
    if (previousRow == row) {
        return;
    }

    // TODO: there must be a way to upgrade the if/else
    if (row != DISPLAY_DIGITS - 1) {
        drawNumber(numberArr[row], row);
    }
    else {  // draw clockDivider
        drawNumber(10, row);
    }
}

void drawNumber(const uint8_t number, const uint8_t digit) {
    uint16_t byteValue = 0;
    if (screenOn) {
        if (blink) {
            switch (editableDigits) {
            case 0:  // hours digits
                if (digit == 0 || digit == 1) {
                    return;
                }
                break;
            case 1:  // hours digits
                if (digit == 2 || digit == 3) {
                    return;
                }
                break;
            default:
                break;
            }
        }
        byteValue = getDigit(number) | getDigitPosition(digit);
    }
    if (previousByteValue == byteValue) {
        return;
    }
    digitalWrite(BLOCK, LOW);
    digitalWrite(STCP, LOW);  // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA

    shiftOut(DS, SHCP, LSBFIRST, byteValue);
    shiftOut(DS, SHCP, LSBFIRST, byteValue >> 8);  // Using a daisy chained 2x8 bit 74HC595N requires a shift right

    digitalWrite(STCP, HIGH);  // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
    digitalWrite(BLOCK, HIGH);
    previousByteValue = byteValue;
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

void update(const uint32_t time, const stateUtil::MODE mode) {
    if (time < lastUpdate) {  // Saves from the time eventual overflow
        lastUpdate = time;
    }

    uint8_t moduloDiv = DISPLAY_DIGITS;
    if (!clkDiv) {
        moduloDiv--;
    }
    if (time - lastUpdate < UPDATE_TIME) {
        return;
    }


    if (stateUtil::MODE::READ == mode) {
        // setScreenPower(true);
        if (blink) {
            setBlink(false, time);
        }
    }
    else if (stateUtil::MODE::EDIT == mode) {
        if (time - lastBlink > BLINK_TIMER) {
            setBlink(!blink, time);
            // setScreenPower(!screenOn);
        }
    }
    previousRow = row;
    row = (row + 1) % moduloDiv;
    lastUpdate = time;
}

void setScreenPower(const bool on) {
    if (on != screenOn) {
        screenOn = on;
    }
}

void setBlink(const bool on, const int time) {
    if (on != blink) {
        blink = on;
    }
    if (time) {
        lastBlink = time;
    }
}

void toggleClockDivider() {
    clkDiv = !clkDiv;
}

void setEditableField(const uint8_t field) {
    editableDigits = field;
}
};  // namespace timeDisplay

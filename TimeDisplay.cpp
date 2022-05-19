#include "TimeDisplay.h"

#include <Arduino.h>
#include "Util.h"
namespace timeDisplay {

// TODO: use bits instead of bools. Research must be made
uint16_t lastUpdate = 0;  // time in ms
uint16_t lastBlink = 0;   // time in ms

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
        byteValue = getDigit(number) + getDigitPosition(digit);
    }
    if (previousByteValue == byteValue) {
        return;
    }
    digitalWrite(STCP, LOW);  // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA

    shiftOut(DS, SHCP, LSBFIRST, byteValue);
    shiftOut(DS, SHCP, LSBFIRST, byteValue >> 8);  // Using a daisy chained 2x8 bit 74HC595N requires a shift right

    digitalWrite(STCP, HIGH);  // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
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

void update(const uint16_t time, stateUtil::MODE mode) {
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

void setScreenPower(bool on) {
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

void setEditableField(uint8_t field) {
    editableDigits = field;
}
};  // namespace timeDisplay

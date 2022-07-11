#include <Arduino.h>
#include "LedArray.h"
#include "ScreenController.h"

namespace ledArray {

const uint8_t DS = 7;
const uint8_t STCP = 9;
const uint8_t SHCP = 10;
const uint8_t CLOCK_CONTROLLER_PIN = 6;

const uint16_t REFRESH = 500;  // nr of updates per sec
const float UPDATE_TIME = 1000 / REFRESH;
// const uint16_t BLINK_TIMER = 600;
const uint8_t ROWS = 7;

const uint16_t R_ONE = 0b0000000010111111;
const uint16_t R_TWO = 0b0000000011011111;
const uint16_t R_THREE = 0b0000000011101111;
const uint16_t R_FOUR = 0b0000000011110111;
const uint16_t R_FIVE = 0b0000000011111011;
const uint16_t R_SIX = 0b0000000011111101;
const uint16_t R_SEVEN = 0b0000000011111110;

const uint16_t C_ONE = 0b0100000000000000;
const uint16_t C_TWO = 0b0010000000000000;
const uint16_t C_THREE = 0b0001000000000000;
const uint16_t C_FOUR = 0b0000100000000000;
const uint16_t C_FIVE = 0b0000010000000000;

bool screenOn = true;

uint32_t lastUpdate = 0;  // time in ms
uint32_t lastBlink = 0;   // time in ms

uint8_t row = 0;  // current row to draw
uint8_t previousRow = 0;

void setup() {
    // prepare Shift Registers
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
    // pinMode(BLOCK, OUTPUT);
    pinMode(CLOCK_CONTROLLER_PIN, OUTPUT);
    digitalWrite(CLOCK_CONTROLLER_PIN, LOW);
    // /***/
    // digitalWrite(BLOCK, LOW);
    // digitalWrite(STCP, LOW);  // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA

    // uint16_t byteVal = C_ONE | C_TWO | R_ONE;
    // shiftOut(DS, SHCP, LSBFIRST, byteVal);    //TODO: improve this SR
    // shiftOut(DS, SHCP, LSBFIRST, byteVal >> 8);  // Using a daisy chained 2x8 bit 74HC595N requires a shift right

    // digitalWrite(STCP, HIGH);  // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
    // digitalWrite(BLOCK, HIGH);  //LOCK THE WRITE
}

void update(const uint32_t time, const stateUtil::MODE mode) {
    if (time < lastUpdate) {  // Saves from the time eventual overflow
        lastUpdate = time;
    }

    if (time - lastUpdate < UPDATE_TIME) {
        return;
    }
    digitalWrite(CLOCK_CONTROLLER_PIN, HIGH);

    digitalWrite(STCP, LOW);  // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA

    uint16_t byteVal = C_ONE | C_TWO | C_THREE | C_FOUR | C_FIVE; //| R_ONE;
    //todo: experimental
    switch (previousRow) {
    case 0:
        byteVal |= R_ONE;
        break;
    case 1:
        byteVal |= R_TWO;
        break;
    case 2:
        byteVal |= R_THREE;
        break;
    case 3:
        byteVal |= R_FOUR;
        break;
    case 4:
        byteVal |= R_FIVE;
        break;
    case 5:
        byteVal |= R_SIX;
        break;
    case 6:
        byteVal |= R_SEVEN;
        break;
    }


    shiftOut(DS, SHCP, LSBFIRST, byteVal);    //TODO: improve this SR
    shiftOut(DS, SHCP, LSBFIRST, byteVal >> 8);  // Using a daisy chained 2x8 bit 74HC595N requires a shift right

    digitalWrite(STCP, HIGH);  // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
    digitalWrite(CLOCK_CONTROLLER_PIN, LOW);
    previousRow = (previousRow + 1) % 7; //todo: magic number
    lastUpdate = time;
}


void setScreenPower(const bool on) {
    if (on != screenOn) {
        screenOn = on;
    }
}

}; //namespace ledArray
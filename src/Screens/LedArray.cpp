#include <Arduino.h>
#include "LedArray.h"
#include "ArrayCharacters.h"
#include "ScreenController.h"
// #include "math.h"
namespace ledArr {

const uint8_t DS = 7;
const uint8_t STCP = 9;
const uint8_t SHCP = 10;
//controls the clock data to go into the registers - HIGH = OPEN
const uint8_t CLOCK_CONTROLLER_PIN = 6;

const uint16_t REFRESH = 500;  // nr of updates per sec
const float UPDATE_TIME = 1000 / REFRESH;
const float UPDATE_BUFFER_TIME = 250; //ms

// const uint16_t BLINK_TIME = 600;
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

const uint8_t STRING_MAX_SIZE = 15; //counting with

const uint8_t BUFFER_MAX_CHARACTERS = STRING_MAX_SIZE * arrayChar::SIZE_OF_CHARS + STRING_MAX_SIZE; //counting with


bool screenOn = true;

uint32_t lastUpdate = 0;  // time in ms
uint32_t lastBlink = 0;   // time in ms
uint32_t lastBufferUpdate = 0;   // time in ms


uint8_t row = 0;  // current row to draw
uint8_t previousRow = 0;

uint16_t charBuffer[BUFFER_MAX_CHARACTERS] = { 0 };
int8_t bufferIdx = -ROWS;
uint8_t bufferSize = 0;
char* previousStr;

uint16_t getBufferData(const uint8_t rowNum) {
    int8_t idx = bufferIdx + rowNum;
    if (idx < 0 || idx > bufferSize) {
        return 0;
    }
    return charBuffer[idx];
}

/**
 * @brief Get the byte value of row
 * rowNum = [0,ROWS]
 * @return uint16_t
 */
uint16_t getRow(const uint8_t rowNum) {
    uint16_t byteVal = 0;
    if (rowNum < 0 || rowNum > ROWS) {
        return byteVal;
    }
    switch (row) {

    case 1:
        return R_TWO;
        break;
    case 2:
        return R_THREE;
        break;
    case 3:
        return R_FOUR;
        break;
    case 4:
        return R_FIVE;
        break;
    case 5:
        return R_SIX;
        break;
    case 6:
        return R_SEVEN;
        break;
    default:
        return R_ONE;
        break;
    }
}

void setup() {
    // prepare Shift Registers
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
    //prepare controller pin
    pinMode(CLOCK_CONTROLLER_PIN, OUTPUT);
    digitalWrite(CLOCK_CONTROLLER_PIN, LOW);
}

void update() {
    const uint32_t time = millis();
    if (time < lastUpdate || time < lastBufferUpdate || time < lastBlink) {  // Saves from the time eventual overflow
        lastUpdate = time;
        lastBufferUpdate = time;
        lastBlink < time;
    }

    if (time - lastBufferUpdate > UPDATE_BUFFER_TIME) {
        if (bufferIdx == bufferSize + min(bufferSize, ROWS) - 1) {
            bufferIdx = -ROWS;
        }
        else {
            bufferIdx = (bufferIdx + 1) % (bufferSize + min(bufferSize, ROWS));
        }
        lastBufferUpdate = time;
    }

    if (time - lastUpdate < UPDATE_TIME) {
        return;
    }

    digitalWrite(CLOCK_CONTROLLER_PIN, HIGH);
    digitalWrite(STCP, LOW);  // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA

    uint16_t byteVal = getBufferData(row) | getRow(row); //| R_ONE;

    shiftOut(DS, SHCP, LSBFIRST, byteVal);    //TODO: improve this SR
    shiftOut(DS, SHCP, LSBFIRST, byteVal >> 8);  // Using a daisy chained 2x8 bit 74HC595N requires a shift right

    digitalWrite(STCP, HIGH);  // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
    digitalWrite(CLOCK_CONTROLLER_PIN, LOW);

    previousRow = row;
    row = (row + 1) % ROWS;
    lastUpdate = time;
}


void setScreenPower(const bool on) {
    screenOn = on;

}

void draw(const char* str) {    //draw being called constantly is bad
    //TODO: use double buffer, one to write another to read AND QUEUEING
    uint8_t idx = 0;
    for (int i = 0; i < strlen(str); i++) {
        arrayChar::CharArr val = arrayChar::toLEDChar(str[i]);

        if (idx + val.size > BUFFER_MAX_CHARACTERS) {
            break;
        }
        for (int j = 0; j < val.size; j++) {
            charBuffer[idx + j] = val.vals[j];
        }
        idx += val.size;
        charBuffer[idx++] = arrayChar::SPACE_BETWEEN_CHARS; //add space betwenn chars
    }
    bufferSize = idx;

}
}; //namespace ledArr
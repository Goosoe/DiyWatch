#include <Arduino.h>
#include "LedArray.h"
#include "ArrayCharacters.h"
#include "../Util.h"

namespace ledArr {

const uint8_t DS = 7;
const uint8_t STCP = 9;
const uint8_t SHCP = 10;
//controls the clock data to go into the registers - HIGH = OPEN
const uint8_t CLOCK_CONTROLLER_PIN = 6;

const uint16_t REFRESH = 500;  // nr of updates per sec
const float UPDATE_TIME = 1000 / REFRESH;
const float UPDATE_BUFFER_TIME = 100; //ms

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

const uint8_t STRING_MAX_SIZE = 15;
const uint8_t BUFFER_MAX_CHARACTERS = STRING_MAX_SIZE * arrayChar::SIZE_OF_CHARS + STRING_MAX_SIZE; //counting with spaces

const uint8_t NUM_OF_DISPLAY_BUFFERS = 2;


uint32_t lastUpdate = 0;  // time in ms
uint32_t lastBufferUpdate = 0;   // time in ms

uint8_t row = 0;  // current row to draw
bool screenOn = true;
// used to define if the text should slide or stay on screen
bool slideText = true;
/**
 * @brief structure with info for the double buffer
 */
struct Buffer {
    int displayBuffer[NUM_OF_DISPLAY_BUFFERS][BUFFER_MAX_CHARACTERS] = { {0}, {0} }; //double buffer display
    uint8_t currentBuffer = 0;
    String bufferText[NUM_OF_DISPLAY_BUFFERS] = { String() }; //todo: char*

    int8_t bufferIdx = -ROWS; // used as a comparison with bufferSize. When they are equal, we know the buffer has slid from right to left 
    uint8_t bufferSize[NUM_OF_DISPLAY_BUFFERS] = { 0 };

} Buffer;

/**
 * @brief initializes the buffer. Should be called during setup
 */
void initBuffer() {
    sendToBuffer(" ", true);
}

/**
 * @brief - resets the bufferIdx
 */
void resetIdx() {
    if (Buffer.bufferText[Buffer.currentBuffer].length() <= 2) {
        Buffer.bufferIdx = 0;
        slideText = false;
    }
    else {
        Buffer.bufferIdx = -ROWS;
        slideText = true;
    };
}

/**
 * @brief - resets the specified buffer and any other necessary parameter in Buffer
 *
 * @param bufferId - which of the buffers to reset
 */
void resetBuffer(uint8_t bufferId) {
    if (Buffer.bufferSize[bufferId] == 0) {
        return;
    }
    for (int i = 0; i < Buffer.bufferSize[bufferId]; i++) {
        Buffer.displayBuffer[bufferId][i] = 0;
    }
    Buffer.bufferSize[bufferId] = 0;
    Buffer.bufferText[Buffer.currentBuffer] = "";
}

/**
 * @brief gets the index of the buffer that is not currently in use
 * @return index
 */
int nextBuffer() {
    return (Buffer.currentBuffer + 1) % NUM_OF_DISPLAY_BUFFERS;
}

/**
 * @brief updates the buffer if spare buffer has next value or resets the idx
 * to print again
 */
void updateBuffer() {
    uint8_t currBuffSize = Buffer.bufferSize[Buffer.currentBuffer];
    if (screenOn && Buffer.bufferIdx++ == currBuffSize) { // current display ended 
        if (Buffer.bufferSize[nextBuffer()] == 0) {
            resetIdx();
            return;
        }
        resetBuffer(Buffer.currentBuffer);
        Buffer.currentBuffer = nextBuffer();
    }
}

/**
 * @brief Get the Buffer display data of a specific row
 *
 * @param rowNum - current row to show
 * @return uint16_t - data to show in specific  rowNum
 */
uint16_t getBufferData(const uint8_t rowNum) {
    int8_t idx = rowNum;
    if (slideText) { //if we want to slide the text, take into account the bufferIdx to do the sliding logic
        idx += Buffer.bufferIdx;
    }
    if (idx < 0 || idx > Buffer.bufferSize[Buffer.currentBuffer]) {
        return 0;
    }
    return Buffer.displayBuffer[Buffer.currentBuffer][idx];
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

/**
 * @brief Write a 16bit into the Shift Register
 *
 * @param byteVal
 */
void writeSR(const uint16_t val) {
    digitalWrite(CLOCK_CONTROLLER_PIN, HIGH);
    digitalWrite(STCP, LOW);  // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA

    shiftOut(DS, SHCP, LSBFIRST, val);    //TODO: improve this SR
    shiftOut(DS, SHCP, LSBFIRST, val >> 8);  // Using a daisy chained 2x8 bit 74HC595N requires a shift right

    digitalWrite(STCP, HIGH);  // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
    digitalWrite(CLOCK_CONTROLLER_PIN, LOW);
}

void setup() {
    // prepare Shift Registers
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
    //prepare controller pin
    pinMode(CLOCK_CONTROLLER_PIN, OUTPUT);
    digitalWrite(CLOCK_CONTROLLER_PIN, LOW);
    initBuffer();
}

void update() {
    if (!screenOn) {
        return;
    }
    const uint32_t time = millis();
    if (time < lastUpdate) {  // Saves from the time eventual overflow
        lastUpdate = time;

    }
    if (time < lastBufferUpdate) {  // Saves from the time eventual overflow
        lastBufferUpdate = time;
    }

    if (time - lastBufferUpdate > UPDATE_BUFFER_TIME) {
        updateBuffer();
        lastBufferUpdate = time;
    }

    if (time - lastUpdate < UPDATE_TIME || Buffer.bufferSize == 0) {
        return;
    }

    writeSR(getBufferData(row) | getRow(row));

    row = (row + 1) % ROWS;
    lastUpdate = time;
}


void setScreenPower(const bool value) {
    if (!value) {
        writeSR(0);
    }
    screenOn = value;
}

void sendToBuffer(const char* text, const bool reset) {
    //TODO: Sring to char buffer
    //use \0 as a stop and sizeof
    String str = String(text);
    //   str.toUpperCase();
    uint8_t nextBuffVal = nextBuffer();

    if (str == Buffer.bufferText[Buffer.currentBuffer] || str == Buffer.bufferText[nextBuffVal]
        || (!reset && Buffer.bufferSize[nextBuffVal] != 0)) {   //TODO: improve this
        return;
    }
    Buffer.bufferText[nextBuffVal] = str;
    int idx = 0;
    for (int i = 0; i < str.length(); i++) {
        arrayChar::CharArr val = arrayChar::toLEDChar(str[i]);
        if (idx + val.size > BUFFER_MAX_CHARACTERS) {
            break;
        }
        for (int j = 0; j < val.size; j++) {
            Buffer.displayBuffer[nextBuffVal][idx + j] = val.vals[j];
        }
        idx += val.size;
        if (i + 1 < str.length()) { // if not last char
            Buffer.displayBuffer[nextBuffVal][idx++] = 0; //add space between chars
        }
    }
    Buffer.bufferSize[nextBuffVal] = idx;
    if (reset) {
        resetBuffer(Buffer.currentBuffer);
        Buffer.currentBuffer = nextBuffVal;
        resetIdx();
    }
}
}; //namespace ledArr
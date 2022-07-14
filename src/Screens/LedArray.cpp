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
const float UPDATE_BUFFER_TIME = 125; //ms

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

bool screenOn = true;

uint32_t lastUpdate = 0;  // time in ms
uint32_t lastBlink = 0;   // time in ms
uint32_t lastBufferUpdate = 0;   // time in ms

uint8_t row = 0;  // current row to draw
uint8_t previousRow = 0;


struct Buffer {
    int displayBuffer[NUM_OF_DISPLAY_BUFFERS][BUFFER_MAX_CHARACTERS] = { {0}, {0} }; //double buffer display
    uint8_t currentBuffer = 0;
    String bufferText[NUM_OF_DISPLAY_BUFFERS] = { String() };

    int8_t bufferIdx = -ROWS;
    uint8_t bufferSize[NUM_OF_DISPLAY_BUFFERS] = { 0 };

} Buffer;

void initBuffer() {
    sendToBuffer(" ", true);
}
void resetIdx() {
    Buffer.bufferIdx = -ROWS;
}

//cleans everything that has in buffer
void resetBuffer(uint8_t bufferId) {
    if (Buffer.bufferSize[bufferId] == 0) {
        return;
    }
    for (int i = 0; i < Buffer.bufferSize[bufferId]; i++) {
        Buffer.displayBuffer[bufferId][i] = 0;
    }
    resetIdx();
    Buffer.bufferSize[bufferId] = 0;
    Buffer.bufferText[Buffer.currentBuffer] = "";
}
int nextBuffer() {
    return (Buffer.currentBuffer + 1) % NUM_OF_DISPLAY_BUFFERS;
}

/**
 * @brief updates the buffer if has next value or resets the idx
 */
void updateBuffer() {
    if (Buffer.bufferSize[nextBuffer()] == 0) {
        resetIdx();
        return;
    }
    resetBuffer(Buffer.currentBuffer);
    Buffer.currentBuffer = nextBuffer();
}

uint16_t getBufferData(const uint8_t rowNum) {
    int8_t idx = Buffer.bufferIdx + rowNum;
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
    const uint32_t time = millis();
    if (time < lastUpdate) {  // Saves from the time eventual overflow
        lastUpdate = time;

    }
    if (time < lastBufferUpdate) {  // Saves from the time eventual overflow

        lastBufferUpdate = time;

    }
    if (time < lastBlink) {  // Saves from the time eventual overflow

        lastBlink < time;
    }

    if (time - lastBufferUpdate > UPDATE_BUFFER_TIME) {
        uint8_t currBuffSize = Buffer.bufferSize[Buffer.currentBuffer];
        if (currBuffSize > 0 && Buffer.bufferIdx++ == currBuffSize + min(currBuffSize, ROWS)) { // current display ended 
            updateBuffer();
        }
        lastBufferUpdate = time;
    }
    if (time - lastUpdate < UPDATE_TIME || Buffer.bufferSize == 0) {
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

void sendToBuffer(const char* text, const bool reset) {
    String str = String(text);
    str.toUpperCase();
    uint8_t nextBuffVal = nextBuffer();

    if (str == Buffer.bufferText[Buffer.currentBuffer] || str == Buffer.bufferText[nextBuffVal]
        || (!reset && Buffer.bufferSize[nextBuffer()] != 0)) {   //TODO: improve this
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
            Buffer.displayBuffer[nextBuffVal][idx++] = 0; //add space betwenn chars
        }
    }
    Buffer.bufferSize[nextBuffVal] = idx; // + 1;  //index starts at 0, the size is +1
    if (reset) {
        updateBuffer();
    }
}
}; //namespace ledArr
/**
 * MCP7940 I2C comm library
 */

#include <Wire.h>

// #include "DisplaySR.ino"

const uint8_t RTC_ADRESS = 0x6F;  // RTC I2C adress
// TODO: make this code enum

/* TIME-KEEPING REGISTERS (Bytes)*/
const uint8_t SEC_REG = 0x00;
const uint8_t MIN_REG = 0x01;
const uint8_t HOUR_REG = 0x02;
const uint8_t WEEK_DAY_REG = 0x03;
const uint8_t DATE_REG = 0x04;
const uint8_t MONTH_REG = 0x05;
const uint8_t YEAR_REG = 0x06;
const uint8_t CONTROL_REG = 0x07;
const uint8_t OSC_TRIM_REG = 0x08;

/* ALARM REGISTER */

// const uint8_t RTC_READ = 1;
bool clkDiv;

uint8_t frames;

// uint8_t loops;

void setup() {
    displaySetup();
    clkDiv = true;

    frames = 0;
    // loops = 0;
    Wire.begin();
    Wire.setClock(100000);  // 10kHz is the default I2C communication
    Serial.begin(9600);
    writeBit(SEC_REG, 7, 1);   // starting up the oscilattor using the ST bit
    writeBit(HOUR_REG, 6, 1);  // setting 24h pattern
}

void loop() {
    // Wire.requestFrom(RTC_ADRESS, 2, false);
    // readByte(0x00);
    uint8_t size = 6;
    uint8_t timeArr[size] = {0};
    // getSecs(readByte(0x00), arr);
    // getMins(readByte(0x01), arr);
    getTime(timeArr, size);
    drawNumbers(timeArr, size, clkDiv);

    frames++;
    if (frames == 60) {
        frames = 0;
        switchScreenPower();
    }
    // loops++;
    // if (loops % 10 == 0) {
    //     clkDiv = !clkDiv;
    //     loops = 0;
    // }
    // drawNumber(uint8_t(1), uint8_t(0));

    // while (Wire.available()) {  // peripheral may send less than requested

    //     byte b = Wire.read();  // receive a byte as character
    //     Serial.print(b);
    //     // first two bytes are read the same way as minutes and seconds
    //     // Serial.print(getMinOrSecs(Wire.read()));  // print the character
    // }
}
/**
 * @brief Get the Time object
 *
 * @param arr - Array to put the Time either HH.mm.ss or HH.mm
 * @param size
 * @return 0 if ok, 1 if not ok
 */
// TODO; Make size an enum that defines either 4 or 6 digit time
uint8_t getTime(uint8_t* arr, uint8_t size) {
    if (size != 4 && size != 6) {
        return 1;
    }
    uint8_t addr, one, tens = 0;
    if (size == 6) {  // add secs to time array
        addr = readByte(SEC_REG);
        one = addr & 0xF;
        tens = (addr >> 4) & 0x7;
        arr[4] = tens;
        arr[5] = one;
    }
    // TODO: min and sec are the same. optimize this
    addr = readByte(MIN_REG);
    one = addr & 0xF;
    tens = (addr >> 4) & 0x7;
    arr[2] = tens;
    arr[3] = one;

    addr = readByte(HOUR_REG);
    one = addr & 0xF;          // get bit 0 to 3
    tens = (addr >> 4) & 0x3;  // get bit 4
    arr[0] = tens;
    arr[1] = one;

    return 0;
}

/*Receives the second or minute byte and converts it into a readable int*/
// uint8_t getMinOrSecs(byte addr) {
//     uint8_t secOne = addr & 0xF;
//     uint8_t secTens = (addr >> 4) & 0x7;
//     return (secTens * 10) + secOne;
// }

// // TODO:EXPERIMENTAL
// void getSecs(byte time, uint8_t* arr) {
//     uint8_t secOne = time & 0xF;
//     uint8_t secTens = (time >> 4) & 0x7;
//     arr[2] = secTens;
//     arr[3] = secOne;
// }
// // TODO:EXPERIMENTAL
// void getMins(byte time, uint8_t* arr) {
//     uint8_t minOne = time & 0xF;
//     uint8_t minTens = (time >> 4) & 0x7;
//     arr[0] = minTens;
//     arr[1] = minOne;
// }

uint8_t readByte(uint8_t address) {
    byte val = 0;
    Wire.beginTransmission(RTC_ADRESS);            // queues bytes to be sent to a slave with the given register
    Wire.write(address);                           // Request the seconds register
    if (Wire.endTransmission() == 0) {             // end the transmition to send the message written in the line above
        Wire.requestFrom(RTC_ADRESS, uint8_t(8));  // requests the message from the slave
        int bytesReceived = Wire.available();
        // Serial.print("Received bytes: ");
        // Serial.println(bytesReceived);
        val = Wire.read();
        // Serial.println(getMinOrSecs(val));
    }
    // TODO: remove else
    else {
        // Serial.println("poop");
        ;
    }
    return val;
}

void writeByte(uint8_t address, uint8_t value) {
    Wire.beginTransmission(RTC_ADRESS);  // Address the I2C device
    Wire.write(address);                 // Send register address to read from
    Wire.write(value);                   // write the data
    uint8_t i = Wire.endTransmission();  // close transmission and save status
}

/**
 * @brief Writes a specific bit in a register
 *
 * @param reg - register to write
 * @param pos - 0-7, being 7 the most significant bit
 * @param bit - 0 or 1
 */
void writeBit(const uint8_t reg, const uint8_t pos, const uint8_t bit) {
    switch (bit) {
        case 0: {
            uint8_t highValue = 254;  // 1111 1110
            writeByte(reg, readByte(reg) & (highValue << pos));
            break;
        }
        case 1:
            writeByte(reg, readByte(reg) | (bit << pos));
            break;
        default:
            // does nothing
            ;
    }
}
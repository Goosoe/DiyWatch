#include "RTC.h"

#include <Arduino.h>
#include <Wire.h>
namespace mcpRtc {

const uint8_t RTC_ADRESS = 0x6F;  // RTC I2C adress

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

const uint8_t DAYS_IN_WEEK = 7;
const uint16_t STARTING_YEAR = 2020;

void setup() {
    Wire.begin();
    Wire.setClock(100000);    // 10kHz is the default I2C communication frequency
    writeBit(SEC_REG, 7, 1);  // starting up the oscilattor using the ST bit
    writeBit(HOUR_REG, 6, 0);   //hour format (0 = 24h, 1 = 12h)
}

uint8_t getTime(uint8_t* arr, const uint8_t size) {
    //TODO: sizeof?
    if (size != 4 && size != 6) {
        return 0;
    }
    uint8_t addr, ones, tens = 0;
    if (size == 6) {  // add secs to time array
        addr = readByte(SEC_REG);
        ones = addr & 0xF;
        tens = (addr >> 4) & 0x7;
        arr[4] = tens;
        arr[5] = ones;
    }
    // TODO: min and sec are the same. optimize this
    addr = readByte(MIN_REG);
    ones = addr & 0xF;
    tens = (addr >> 4) & 0x7;
    arr[2] = tens;
    arr[3] = ones;

    addr = readByte(HOUR_REG);
    ones = addr & 0xF;          // get bit 0 to 3
    tens = (addr >> 4) & 0x3;  // get bit 4 and 5
    arr[0] = tens;
    arr[1] = ones;

    return 1;
}

uint8_t readByte(const uint8_t address) {
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
    return val;
}

void writeByte(const uint8_t address, const uint8_t value) {
    Wire.beginTransmission(RTC_ADRESS);  // Address the I2C device
    Wire.write(address);                 // Send register address to read from
    Wire.write(value);                   // write the data
    uint8_t i = Wire.endTransmission();  // close transmission and save status
}

void writeBit(const uint8_t address, const uint8_t pos, const uint8_t bit) {
    if (bit < 0 || bit > 1 || pos < 0 || pos > 7) {
        return;
    }
    uint8_t val = bit << pos;
    int8_t bit_mask = 0b00000001 << pos;
    writeByte(address, readByte(address) & (~bit_mask) | val);
}

void addHour() {
    uint8_t addr = readByte(HOUR_REG);

    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0x3;  // get bit 4 and 5
    uint8_t bit_mask = 0b00111111;

    switch (ones) {
    case 3:
        if (tens == 2) {
            addr = addr & (~bit_mask);    // resets the hour ones and tens to 0
        }
        else {
            addr++;
        }
        break;

    case 9: {
        tens = (tens + 1) << 4;
        addr = (addr & (~bit_mask)) | tens;     // resets the hour ones to 0 and sets the new tens value
    }
          break;
    default:
        addr++;
        break;
    }
    writeByte(HOUR_REG, addr);
}

void addMinute() {  //TODO: reset seconds when minute is added?
    uint8_t addr = readByte(MIN_REG);

    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0x7;  // get bit 4 to 6
    int8_t bit_mask = 0b01111111;

    switch (ones) {
    case 9:
        if (tens == 5) {
            addr = addr & (~bit_mask);    // resets minute hour ones and tens to 0
        }
        else {
            tens = (tens + 1) << 4;
            addr = (addr & (~bit_mask)) | tens;     // resets the minute ones to 0 and sets the new tens value
        }
        break;
    default:
        addr++;
        break;
    }
    writeByte(MIN_REG, addr);
}

uint8_t getWeekDay() {
    return  readByte(WEEK_DAY_REG) & 0x7;
}

uint8_t addWeekDay() {
    writeByte(WEEK_DAY_REG, (getWeekDay() + 1) % DAYS_IN_WEEK);
}

uint8_t getMonth() {
    uint8_t addr = readByte(MONTH_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0x1;  // get bit 4
    return tens * 10 + ones;

}

uint8_t addMonth() {
    uint8_t addr = readByte(MONTH_REG);

    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0x1;  // get bit 4
    uint8_t bit_mask = 0b00011111;

    switch (ones) {
    case 2:
        if (tens == 1) {
            addr = addr & (~bit_mask);    // resets month to 0
        }
    default:
        addr++;
        break;
    }
    writeByte(MIN_REG, addr);
}

uint8_t getYear() {
    uint8_t addr = readByte(YEAR_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0xA;  // get bit 4 to 7
    return +tens * 10 + ones;
}

uint8_t addYear() {
    uint8_t addr = readByte(YEAR_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0xF;  // get bit 4 to 6
    uint8_t bit_mask = 0b11111111;

    switch (ones) {
    case 9:
        if (tens == 15) {
            addr = addr & (~bit_mask);    // resets ones and tens to 0
        }
        else {
            tens = (tens + 1) << 4;
            addr = (addr & (~bit_mask)) | tens;     // resets the minute ones to 0 and sets the new tens value
        }
        break;
    default:
        addr++;
        break;
    }
    writeByte(YEAR_REG, addr);
}





};  // namespace mcpRtc
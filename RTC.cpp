#include "RTC.h"

#include <Arduino.h>
#include <Wire.h>
namespace mcpRtc {

void setup() {
    Wire.begin();
    Wire.setClock(100000);    // 10kHz is the default I2C communication frequency
    writeBit(SEC_REG, 7, 1);  // starting up the oscilattor using the ST bit
    writeBit(HOUR_REG, 6, 0);   //hour format (0 = 24h, 1 = 12h)
}

uint8_t getTime(uint8_t* arr, const uint8_t size) {
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
    uint8_t ones, tens = 0;
    uint8_t addr = readByte(HOUR_REG);

    ones = addr & 0xF;          // get bit 0 to 3
    tens = (addr >> 4) & 0x3;  // get bit 4 and 5
    switch (ones) {
    case 3:
        if (tens == 2) {
            int8_t bit_mask = 0b00111111;
            addr = addr & (~bit_mask);    // resets the hour ones and tens to 0
        }
        else {
            addr++;
        }
        break;

    case 9: {
        tens = (tens + 1) << 4;
        int8_t bit_mask = 0b00111111;
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

    uint8_t ones, tens = 0;
    uint8_t addr = readByte(MIN_REG);

    ones = addr & 0xF;          // get bit 0 to 3
    tens = (addr >> 4) & 0x7;  // get bit 4 to 6

    switch (ones) {
    case 9:
        if (tens == 5) {
            int8_t bit_mask = 0b01111111;
            addr = addr & (~bit_mask);    // resets minute hour ones and tens to 0
        }
        else {
            tens = (tens + 1) << 4;
            int8_t bit_mask = 0b01111111;
            addr = (addr & (~bit_mask)) | tens;     // resets the minute ones to 0 and sets the new tens value
        }
        break;
    default:
        addr++;
        break;
    }
    writeByte(MIN_REG, addr);
}

};  // namespace mcpRtc
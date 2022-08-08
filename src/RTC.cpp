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

/* ALARM REGISTERS (Bytes)*/
const uint8_t MIN_ALR_REG = 0x0B;
const uint8_t HOUR_ALR_REG = 0x13;
const uint8_t WEEK_ALR0_REG = 0x0D;
const uint8_t WEEK_ALR1_REG = 0x14;

void writeAlarmMask(uint8_t address, uint8_t mask) {
    writeByte(address, readByte(address) | (mask << 4));
}

void setup() {
    Wire.begin();
    Wire.setClock(100000);    // 10kHz is the default I2C communication frequency
    writeBit(SEC_REG, 7, 1);  // starting up the oscilattor using the ST bit
    writeBit(HOUR_REG, 6, 0);   //hour format (0 = 24h, 1 = 12h)
    writeBit(HOUR_ALR_REG, 6, 0);   //alarm hour format (0 = 24h, 1 = 12h)
    writeAlarmMask(WEEK_ALR0_REG, 0b001); // ALR0 - set minutes mask
    writeAlarmMask(WEEK_ALR1_REG, 0b010); // ALR1 - set hour mask
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

uint8_t addMinuteAux(uint8_t reg) {  //TODO: reset seconds when minute is added?
    uint8_t addr = readByte(reg);

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
    writeByte(reg, addr);
    return tens * 10 + ones;
}

uint8_t addHourAux(uint8_t reg) {
    uint8_t addr = readByte(reg);

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
    writeByte(reg, addr);
    return tens * 10 + ones;
}

void addHour() {
    addHourAux(HOUR_REG);
}

void addMinute() {  //TODO: reset seconds when minute is added?
    addMinuteAux(MIN_REG);
}

uint8_t getSeconds() {
    uint8_t addr = readByte(SEC_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0x7;  // get bit 4 to 6
    return tens * 10 + ones;
}

uint8_t getWeekDay() {
    return readByte(WEEK_DAY_REG) & 0x7;
}

uint8_t addWeekDay() {
    uint8_t newWeekDay = (getWeekDay() % 7 + 1);
    writeByte(WEEK_DAY_REG, newWeekDay);    //7 days in the week
    return newWeekDay;
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
    addr++; //added here to prevent defaults and repetition
    switch (ones) {
    case 2:
        if (tens == 1) {
            addr = addr & (~bit_mask) | 0x1;    // resets month to 1
        }
        break;
    case 9: {
        addr = (tens + 1) << 4;   // resets the ones to 0 and sets the new tens value
        break;
    }
    }
    writeByte(MONTH_REG, addr);    //12 months in a year
    return tens * 10 + ones;
}

uint16_t getYear() {
    uint8_t addr = readByte(YEAR_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0xF;  // get bit 4 to 7
    return tens * 10 + ones;
}

uint16_t addYear() {
    uint8_t addr = readByte(YEAR_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0xF;  // get bit 4 to 6
    uint8_t bit_mask = 0b11111111;
    addr++; //added here to prevent defaults and repetition
    switch (ones) {
    case 9: {
        if (tens == 9) {
            addr = addr & (~bit_mask) | 0x1;    // resets ones to 1 and tens to 0
        }
        else {
            addr = (tens + 1) << 4;    // resets the minute ones to 0 and sets the new tens value
        }
        break;
    }
    }
    writeByte(YEAR_REG, addr);
    return tens * 10 + ones;
}

uint8_t addDate() {
    uint8_t addr = readByte(DATE_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0x3;  // get bit 4 and 5
    uint8_t bit_mask = 0b00111111;
    addr++; //added here to prevent defaults and repetition of this sum
    switch (ones) {
    case 1: {
        if (tens == 3) {
            addr = addr & (~bit_mask) | 0x1;    // resets the hour ones and tens to 1
        }
        break;
    }
    case 9: {
        addr = (tens + 1) << 4;     // resets the ones to 0 and sets the new tens value
        break;
    }
    }
    writeByte(DATE_REG, addr);
    return tens * 10 + ones;
}

uint8_t getDate() {
    uint8_t addr = readByte(DATE_REG);
    uint8_t ones = addr & 0xF;          // get bit 0 to 3
    uint8_t tens = (addr >> 4) & 0x3;  // get bit 4 to 7
    return tens * 10 + ones;
}

uint8_t getAlrHour() {
    return addHourAux(HOUR_ALR_REG);
}

uint8_t getAlrMinute() {
    return addMinuteAux(MIN_ALR_REG);
}

uint8_t addAlrHour() {
    return addHourAux(HOUR_ALR_REG);
}

uint8_t addAlrMinute() {
    return addMinuteAux(MIN_ALR_REG);
}

uint8_t toggleAlarm() {
    uint8_t alarmVal = readByte(CONTROL_REG) >> 0x4 & 0x1;
    alarmVal = (alarmVal + 1) % 2;
    writeBit(CONTROL_REG, 4, alarmVal); // toggle ALM0EN register
    writeBit(CONTROL_REG, 5, alarmVal); // toggle ALM1EN register
    return alarmVal;
}
uint8_t getAlarmFlags() {
    uint8_t result = 0;
    uint8_t val = readByte(WEEK_ALR0_REG);
    result += val >> 3 & 0b1;
    val = readByte(WEEK_ALR1_REG);
    result += val >> 2 & 0b10;
    return result;
}

void resetAlarmFlag(uint8_t alarmId) {
    if (alarmId < 0 || alarmId > 2) {
        return;
    }
    uint8_t address = WEEK_ALR0_REG;
    if (alarmId) {
        address = WEEK_ALR1_REG;
    }
    uint8_t regVal = readByte(address);
    writeByte(address, regVal & 0b11110111);
}

void getAlrTime(uint8_t* buff) {
    uint8_t addr = readByte(MIN_ALR_REG);
    uint8_t ones = addr & 0xF;
    uint8_t tens = (addr >> 4) & 0x7;
    buff[2] = tens;
    buff[3] = ones;

    addr = readByte(HOUR_ALR_REG);
    ones = addr & 0xF;          // get bit 0 to 3
    tens = (addr >> 4) & 0x3;  // get bit 4 and 5
    buff[0] = tens;
    buff[1] = ones;
}
};  // namespace mcpRtc
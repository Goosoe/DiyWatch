#include "RTC.h"

#include <Arduino.h>
#include <Wire.h>
namespace mcpRtc {

void setup() {
    Wire.begin();
    Wire.setClock(100000);    // 10kHz is the default I2C communication frequency
    writeBit(SEC_REG, 7, 1);  // starting up the oscilattor using the ST bit
    writeBit(HOUR_REG, 6, 1);
}

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
        default:;  // does nothing
    }
}
}  // namespace mcpRtc
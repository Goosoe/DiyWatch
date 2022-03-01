/**
 * MCP7940 I2C comm library
 */

#include <Wire.h>
// RTC write adress
const uint8_t RTC_ADRESS = 0x6F;
const uint8_t RTC_READ = 1;

void setup() {
    Wire.begin();
    Wire.setClock(100000);  // 10kHz is the default I2C communication
    Serial.begin(9600);
    writeBit(0x00, 7, 1);  // starting up the oscilattor
}

void loop() {
    //    Wire.requestFrom(RTC_ADRESS, 2, false);
    readByte(0x00);
    // uint8_t arr[2];
    // getSecs(readByte(0x00), arr);
    // for (int i = 0; i < 2; i++) {
    //     drawNumber(arr[i], i);
    // }

    // while (Wire.available()) {  // peripheral may send less than requested

    //     byte b = Wire.read();  // receive a byte as character
    //     Serial.print(b);
    //     // first two bytes are read the same way as minutes and seconds
    //     // Serial.print(getMinOrSecs(Wire.read()));  // print the character
    // }

    delay(1000);
}
/*Receives the second or minute byte and converts it into a readable int*/
uint8_t getMinOrSecs(byte time) {
    uint8_t secOne = time & 0xF;
    uint8_t secTens = (time >> 4) & 0x7;
    return (secTens * 10) + secOne;
}

// TODO:EXPERIMENTAL
void getSecs(byte time, uint8_t* arr) {
    uint8_t secOne = time & 0xF;
    uint8_t secTens = (time >> 4) & 0x7;
    arr[0] = secTens;
    arr[1] = secOne;
}

uint8_t readByte(uint8_t address) {
    byte val = 0;
    Wire.beginTransmission(RTC_ADRESS);            // queues bytes to be sent to a slave with the given register
    Wire.write(address);                           // Request the seconds register
    if (Wire.endTransmission() == 0) {             // end the transmition to send the message written in the line above
        Wire.requestFrom(RTC_ADRESS, uint8_t(8));  // requests the message from the slave
        int bytesReceived = Wire.available();
        Serial.print("Received bytes: ");
        Serial.println(bytesReceived);
        val = Wire.read();
        Serial.println(val);
        Serial.println(getMinOrSecs(val));
    } else {
        Serial.println("poop");
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
 * @brief
 *
 * @param reg
 * @param pos - 0-7, being 7 the most significant bit
 * @param bit - 0 or 1
 */
void writeBit(const byte reg, uint8_t pos, const uint8_t bit) {
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
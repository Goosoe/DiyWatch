/**
 * @file MCP7940.ino
 * @author Goosoe
 * @brief
 * MCP7940 I2C comm library
 * This library is by far the most complete and was created so I could have a better understanding
 * of I2C and RTC IC's.
 * @copyright Copyright (c) 2022
 */
#pragma once
#include <stdint.h>

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

/**
 * @brief Setup of this specific RTC.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief Reads the byte
 * @param address address to read
 * @return uint8_t byte info
 */
uint8_t readByte(uint8_t address);

/**
 * @brief Writes a byte in address
 * @param address adress to read
 * @param value byte
 */
void writeByte(uint8_t address, uint8_t value);

/**
 * @brief Writes a bit in address
 * @param address adress write
 * @param pos position of the bit in the byte [0,7]
 * @param bit bit value - 1 or 0
 */
void writeBit(const uint8_t address, const uint8_t pos, const uint8_t bit);

/**
 * @brief Get the time value stored
 *
 * @param arr array where the data will be returned
 * @param size Size of the array to send. if 4 - sends hhmm if 6 hhmmss
 * @return 1 if success
 */
uint8_t getTime(uint8_t* arr, uint8_t size);

/**
 * @brief Adds an hour to the RTC register.
 * All the tens and ones logic is included
 */
void addHour();

/**
 * @brief Adds an minute to the RTC register.
 * All the tens and ones logic is included
 */
void addMinute();

// void increaseTime(uint8_t* arr, uint8_t size);

};  // namespace mcpRtc
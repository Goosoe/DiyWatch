/**
 * @file MCP7940.ino
 * @author Goosoe
 * @brief
 * MCP7940 I2C comm library
 * This library is not complete and was created so I could have a better understanding
 * of I2C and RTC IC's.
 * @copyright Copyright (c) 2022
 */
#pragma once
#include <stdint.h>

namespace mcpRtc {

/**
 * @brief Setup.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief Reads the byte
 * @param address address to read
 * @return uint8_t byte info
 */
uint8_t readByte(const uint8_t address);

/**
 * @brief Writes a byte in address
 * @param address adress to read
 * @param value byte
 */
void writeByte(const uint8_t address, const uint8_t value);

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
uint8_t getTime(uint8_t* arr, const uint8_t size);

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
/**
 * @file MCP7940.ino
 * @author Goosoe
 * @brief
 * MCP7940 I2C comm library
 * This library is by far the most complete and was created so I could have a better understanding
 * of I2C and RTC IC's.
 * @version 0.1
 * @date 2022-03-19
 * @copyright Copyright (c) 2022
 */
#pragma once
#include <stdint.h>

namespace mcpRtc {

void setup();

uint8_t readByte(uint8_t address);

void writeByte(uint8_t address, uint8_t value);

void writeBit(const uint8_t reg, const uint8_t pos, const uint8_t bit);

uint8_t getTime(uint8_t* arr, uint8_t size);
};  // namespace mcpRtc
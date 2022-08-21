/**
 * @file RTC.h
 * @author Goosoe
 * @brief
 * RTC library for the MCP7940M
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

/****TIME FUNCTIONS****/
uint8_t getSeconds();

uint8_t getWeekDay();

uint8_t addWeekDay();

uint8_t getMonth();

uint8_t addMonth();

uint16_t getYear();

uint16_t addYear();

uint8_t addDate();

uint8_t getDate();

//TODO: reset year

/****ALARM FUNCTIONS****/
uint8_t addAlrHour();

uint8_t addAlrMinute();

uint8_t toggleAlarm();

/**
 * @brief gets the ALMIF flags in an uint form
 * 0bn0 - n holds the value for the alarm register 0
 * 0b0n - n holds the value for the alarm register 1
 * @return uint8_t - [0,3]
 */
uint8_t getAlarmFlags();

/**
 * @brief Checks the ALMIF flag
 * alarmId = 0 - Alarm register 0
 * alarmId = 1 - Alarm register 1
 * @param alarmId  [0,1]
 */
void resetAlarmFlag(uint8_t alarmId);

/**
 * @brief gets the alarm hour and minutes in the format hhmm.
 */
void getAlrTime(uint8_t* buff);
};  // namespace mcpRtc

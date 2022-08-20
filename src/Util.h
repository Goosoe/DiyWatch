/**
 * @file Util.h
 * @author Goosoe
 * @brief This file has all enums and functions required for multiple files
 */
#pragma once
#include <stdint.h>

namespace stateUtil {
enum MODE {
    READ,
    EDIT

};

enum STATE {
    TIME,
    SENSORS,
    ALARM
};
};// namespace stateUtil
namespace util {

/**
 * @brief converts a number to a name of the days of the week
 */
void numToDayWeek(const uint8_t val, char* out, uint8_t& index);

/**
 * @brief converts a number to a name of the month
 */
void numToMonth(uint8_t val, char* out, uint8_t& index); 

/**
 * @brief converts a int number to its char representation
 */
void numToChar(uint16_t val, char* out, uint8_t& index);

/**
 * @brief converts a bunch of data into a date format "dd ww mm yy"
 */
void createDate(char* dateArr, const uint8_t day, const uint8_t weekDay, const uint8_t month, const uint16_t year);
}; // namespace util

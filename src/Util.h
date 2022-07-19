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
    CHRONOMETER,
    ALARM
};
};// namespace stateUtil
namespace util {
void createDate(char* dateArr, const uint8_t day, const uint8_t weekDay, const uint8_t month, const uint16_t year);
}; // namespace util
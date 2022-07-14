/**
 * @file Util.h
 * @author Goosoe
 * @brief This file has all enums and functions required for multiple files
 */
#pragma once
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
}; // namespace stateUtil
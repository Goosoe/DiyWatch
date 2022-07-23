/**
 * @file Sensors.h
 * @author Goosoe
 * @brief This library has an API to receive data from sensors
 */
#pragma once
#include <stdint.h>
namespace sensors {
/**
 * @brief Setup.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief Checks for input values and invokes the observer function
 */
void update();

/**
 * @brief Get the average temperature
 * @return int8_t
 */
int8_t getTemp();
};  //namespace sensors
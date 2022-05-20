/**
 * @file Sensors.h
 * @author Goosoe
 * @brief This library has an API to receive data from sensors
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <stdint.h>
namespace sensors {

void setup();
void update(const uint32_t time);

int8_t getTemp();
};  //namespace sensors
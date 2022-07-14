/**
 * @file Sensors.h
 * @author Goosoe
 * @brief This library has an API to receive data from sensors
 */
#pragma once
#include <stdint.h>
namespace sensors {

void setup();

void update();

int8_t getTemp();
};  //namespace sensors
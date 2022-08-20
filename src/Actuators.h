/**
 * @file Actuators.h
 * @author Goosoe
 * @brief API for the actuators
 */

#pragma once
namespace actuators {
/**
 * @brief setup.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief updates the actuators
 */
void update();

/**
 * @brief turns the vibration motor actuator on or off
 */
void setVibrator(bool on);
}

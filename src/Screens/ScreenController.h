/**
* @file ScreenController.h
* @author Goosoe
* @brief API to control all the displays for the clock
*/

#pragma once
#include <stdint.h>
#include "../Util.h"
#include <string.h>

namespace screenController {

const uint8_t MAX_EDITABLE_FIELDS = 2;  //TODO: update when adding more displays

// pins that control the NPN transistor that opens the clock to the specific display
/**
 * @brief Setup.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief Updates the ScreenController
 * @param time current time
 * @param mode current mode
 */
void update();

/**
 * @brief Resets the edit mode.
 * Sets the editfield to 0 and blink to false
 */
void resetEditMode(); //TODO: MAKE ENUM

/**
 * @brief updates the EditField so it can alert the necessary displays about editing
 */
void incrementEditField();

/**
 * @brief Sends an array (of size 4) to the seven-segment screen to be drawn
 *
 * @param arr
 */
void SSDraw(const uint8_t* arr);

/**
 * @brief Sends a string (max size 30) to the LED Array screen to be drawn
 *
 * @param str
 */
void LASendToBuffer(const char* str, const bool reset = false);

/**
 * @brief Sets the blink variable.
 * If true, starts the blinking process
 * @param val - value
 */
void setBlink(const bool val);

/**
 * @brief Set the blinkVal
 * If true, the screen is on. Usually used to force an initial state
 * @param val
 */
void setBlinkVal(const bool val);

/**
 * @brief Get the Current EditField value
 *
 * @return uint8_t
 */
uint8_t getEditField();
};  // namespace screenController
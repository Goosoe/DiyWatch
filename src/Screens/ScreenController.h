/**
* @file ScreenController.h
* @author Goosoe
* @brief This library has the API to control all the displays for the clock
* @copyright Copyright (c) 2022
*
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
 * @brief Set the Editable Field in the correct screen
 *
 * @param field
 */
uint8_t setEditableField(const uint8_t field); //TODO: MAKE ENUM

uint8_t incrementEditField();  //TODO:docs

/**
 * @brief Sends an array (of size 4) to the seven-segment screen to be drawn
 *
 * @param arr
 */
void drawSS(const uint8_t* arr);

/**
 * @brief Sends a string (max size 30) to the LED Array screen to be drawn
 *
 * @param str
 */
void drawLA(const char* str);
/**
 * @brief Stops the blink
 *
 */
void setBlink(const bool on);
};  // namespace screenController
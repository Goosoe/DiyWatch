
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

namespace ledArr {
/**
 * @brief Setup.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief Updates the Timedisplay
 *
 * @param time current time
 * @param mode current mode
 */
void update();

/**
 * @brief Set the Screen Power
 *
 * @param on
 */
void setScreenPower(const bool on);

/**
 * @brief Wipes the buffer and adds the string
 *
 * @param str - to write in the buffer/LED Array
 */
void draw(const char* str);

} // namespace ledArr

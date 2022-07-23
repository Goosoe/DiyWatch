
/**
* @file ScreenController.h
* @author Goosoe
* @brief API to control the LED Array
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
 * @brief Updates the display
 *
 * @param time current time
 * @param mode current mode
 */
void update();

/**
 * @brief Set the Screen Power
 *
 * @param val
 */
void setScreenPower(const bool val);

/**
 * @brief Adds str as the next text to show
 * @param reset - Forces the array to show the text imediately, halting the current display
 * @param str - to write in the buffer/LED Array
 */
void sendToBuffer(const char* str, const bool reset = false);

} // namespace ledArr

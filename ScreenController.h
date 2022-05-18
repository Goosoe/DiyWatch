/**
* @file ScreenController.h
* @author Goosoe
* @brief This header has an API to control all the displays for the clock
* @copyright Copyright (c) 2022
*
*/

#pragma once
#include <stdint.h>
#include "Util.h"

namespace screenController {
const uint8_t MAX_EDITABLE_FIELDS = 2;  //TODO: update when adding more displays

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
void update(const int currentTime, const stateUtil::MODE mode);

/**
 * @brief Set the Editable Field in the correct screen
 *
 * @param field
 */
void setEditableField(const uint8_t field); //TODO: MAKE ENUM

/**
 * @brief Sends the time array (of size 4) to the respective screen to be drawn
 *
 * @param timeArr
 */
void drawTime(const uint8_t* timeArr);

/**
 * @brief Stops the blink
 *
 */
void resetBlink(const int currentTime = 0);
};  // namespace screenController
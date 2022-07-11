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

namespace screenController {

const uint8_t MAX_EDITABLE_FIELDS = 2;  //TODO: update when adding more displays

// pins that control the NPN transistor that opens the clock to the specific display
const uint8_t SS_REGISTER_CONTROLLER = 5;
const uint8_t LA_REGISTER_CONTROLLER = 6;
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
void update(const uint32_t time, const stateUtil::MODE mode);

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
void resetBlink(const uint16_t time = 0);
};  // namespace screenController
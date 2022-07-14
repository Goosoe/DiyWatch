/**
 * @file SevenSegment.h
 * @author Goosoe
 * @brief This file has all the functions required to properly write in the 4x7-segment display being used (LTC-2623G)
 * The digits and segments are being controlled by two daisy chained shift registers
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <stdint.h>
#include "../Util.h"

namespace svnSeg {

/**
 * @brief Setup.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief  Gets the byte representation of the digit position
 * 0-3 - Selects a digit left to right
 * 4 - Clock divider
 * @param digit - position [0,4]
 */
uint16_t getDigitPosition(const uint8_t digit);

/**
 * @brief  Gets display byte representation of num
 *       0-9 are numbers
 *       10 - The clock divider
 */

uint16_t getDigit(const uint8_t num);

/**
 * @brief Writes the number array on the display. Left most value goes to the left-most
 * position of the display. If size > 4, it draws the first 4 values
 *
 * @param numberArr - array
 * @param size - [1,n] - size of the given array
 * @param clkDiv - Enables the clock divider in the display
 */
void drawNumbers(const uint8_t* numberArr);

/**
 * @brief Draws a number into the specified digit position
 *
 * @param number
 * @param digit - position [0,4]
 */
void drawNumber(const uint8_t number, const uint8_t digit);  // TODO: Is this useful at all?

/**
 * @brief Updates the seven segment display
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
 * @brief Set the Blink variable
 *
 * @param val
 */
void setBlink(const bool val);

/**
 * @brief Sets the Editable Field. This value is used to know which of the digits are supposed to be edited
 *
 * @param field must be [0,1]
 */
void setEditableField(const uint8_t field);
};  // namespace svnSeg
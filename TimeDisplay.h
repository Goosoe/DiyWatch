/**
 * @file TimeDisplay.h
 * @author Goosoe
 * @brief This file has all the functions required to properly write in the 4x7-segment display being used (LTC-2623G)
 * The digits and segments are being controlled by two daisy chained shift registers
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <stdint.h>
#include "Util.h"

namespace timeDisplay {
const uint8_t DS = 8;
const uint8_t STCP = 9;
const uint8_t SHCP = 10;
// SEGMENT SELECTOR - HIGH IS OFF
const uint16_t ZERO = 0b0000000000010000;
const uint16_t ONE = 0b0100100001110000;
const uint16_t TWO = 0b0001000000100000;
const uint16_t THREE = 0b0000000001100000;
const uint16_t FOUR = 0b0100100001000000;
const uint16_t FIVE = 0b0010000001000000;
const uint16_t SIX = 0b0010000000000000;
const uint16_t SEVEN = 0b0000100001110000;
const uint16_t EIGHT = 0b0000000000000000;
const uint16_t NINE = 0b0000000001000000;
const uint16_t CLOCK_DIVIDER = 0b0001000000000000;

// DIGIT POSITION SELECTOR - LOW IS OFF
const uint16_t D1 = 0b0000001000000000;
const uint16_t D2 = 0b0000000000001000;
const uint16_t D3 = 0b0000000000000100;
const uint16_t D4 = 0b0000000000000010;
const uint16_t L1 = 0b0000010000000000;

const uint16_t REFRESH = 260;  // updates every REFRESH ms
const float UPDATE_TIME = 1000 / REFRESH;
const uint16_t BLINK_TIMER = 600;
const uint8_t DISPLAY_DIGITS = 5;  // The 5th digit is the clock separator

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
 * @brief Updates the Timedisplay
 *
 * @param time current time
 * @param mode current mode
 */
void update(const int time, const stateUtil::MODE mode);

/**
 * @brief Set the Screen Power
 *
 * @param on
 */
void setScreenPower(const bool on);

/**
 * @brief Set the Blink variable
 *
 * @param on
 */
void setBlink(const bool on, const int currentTime = 0);

/**
 * @brief Sets the Editable Field. This value is used to know which of the digits are supposed to be edited
 *
 * @param field must be [0,1]
 */
void setEditableField(const uint8_t field);


// inline void toggleClockDivider();

};  // namespace timeDisplay
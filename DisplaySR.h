/**
 * @file DisplaySR.h
 * @author Goosoe
 * @brief This file has all the functions required to properly write in the 7-segment display being used.
 * The digits and segments are being controlled by two daisy chained shift registers.
 * @version 0.1
 * @date 2022-03-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include <stdint.h>
namespace timeDisplay {
// TODO: use bits instead of bools. Research must be made

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

void drawNumbers(const uint8_t* numberArr, uint8_t size, const bool clkDiv);
/**
 * @brief Draws a number into the specified digit position
 *
 * @param number
 * @param digit - position [0,4]
 */
void drawNumber(const uint8_t number, const uint8_t digit);  // TODO: Is this useful at all?

inline void toggleEditMode();

inline void toggleScreenPower();

inline void toggleClockDivider();
/**
 * @brief Writes the number array on the display. Left most value goes to the left-most
 * position of the display. If size > 4, it draws the first 4 values
 *
 * @param numberArr - array
 * @param size - [1,n] - size of the given array
 * @param clkDiv - Enables the clock divider in the display
 */
}  // namespace timeDisplay
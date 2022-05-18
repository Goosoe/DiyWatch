
#pragma once
#include <stdint.h>

namespace controls {

const uint8_t BUTTON_ONE = 11;
const uint8_t BUTTON_TWO = 12;

const uint16_t REFRESH = 250;  // updates every REFRESH ms
const float UPDATE_TIME = 1000 / REFRESH;
const float LONG_PRESS_TIME = 750;

enum COMMAND {
    NONE,
    B1_PRESS,
    B1_HOLD,
    B2_PRESS,
    B2_HOLD
};

/**
 * @brief Setup.
 * Must be called in the main setup
 */
void setup();

/**
 * @brief Checks for input values and invokes the observer function
 *
 * @param currentTime
 * @param observer function to be invoked after checking for commands
 */
void update(int currentTime, void(*observer)(COMMAND));

// COMMAND_LIST getInput();
};  // namespace controls

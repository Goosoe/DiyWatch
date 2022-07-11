
#pragma once
#include <stdint.h>

namespace controls {

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
 * @param time
 * @param observer function to be invoked after checking for commands
 */
void update(const uint32_t time, void(*observer)(COMMAND));

// COMMAND_LIST getInput();
};  // namespace controls
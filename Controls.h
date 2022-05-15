
#pragma once
#include <stdint.h>

namespace controls {

const uint8_t BUTTON_ONE = 11;
const uint8_t BUTTON_TWO = 12;

const uint16_t REFRESH = 250;  // updates every REFRESH ms
const float UPDATE_TIME = 1000 / REFRESH;
const float LONG_PRESS_TIME = 750;

enum COMMAND { NONE,
               B1_PRESS,
               B1_HOLD,
               B2_PRESS,
               B2_HOLD
};

void setup();
/**
 * for debug purposes - prints the input info
 */
void printInputs();

void update(int currentTime, void(*observer)(COMMAND));

// COMMAND_LIST getInput();
};  // namespace controls

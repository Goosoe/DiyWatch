
// press or hold is declared if the button was released or not in x time
#pragma once
#include <stdint.h>

namespace controls {

const uint8_t BUTTON_ONE = 11;
const uint8_t BUTTON_TWO = 12;

const uint16_t REFRESH = 250;  // updates every REFRESH ms
const float UPDATE_TIME = 1000 / REFRESH;

enum COMMAND { NONE,
               B1_PRESS,
               B2_PRESS,
               B1_HOLD,
               B2_HOLD
};
struct COMMAND_LIST {
    COMMAND b1;
    COMMAND b2;
};

void setup();
/**
 * for debug purposes - prints the input info
 */
void printInputs();

void update(int currentTime);

COMMAND_LIST getInput();
};  // namespace controls

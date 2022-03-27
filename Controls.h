
// press or hold is declared if the button was released or not in x time
#pragma once
#include <stdint.h>

namespace controls {

const uint8_t BUTTON_ONE = 11;
const uint8_t BUTTON_TWO = 12;

// enum COMMANDS { BUTTON_ONE_PRESS,
//                 BUTTON_TWO_PRESS,
//                 BUTTON_ONE_HOLD,
//                 BUTTON_TWO_HOLD,
//                 NONE };

void setup();
};  // namespace controls

// Serial.print("Button one: ");
// Serial.println(digitalRead(BUTTON_ONE));
// Serial.print("Button two: ");
// Serial.println(digitalRead(BUTTON_TWO));

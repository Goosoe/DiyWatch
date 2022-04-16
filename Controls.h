
// press or hold is declared if the button was released or not in x time
#pragma once
#include <stdint.h>

namespace controls {

const uint8_t BUTTON_ONE = 11;
const uint8_t BUTTON_TWO = 12;

const uint16_t REFRESH = 1;
const float UPDATE_TIME = 1000 / REFRESH;

void setup();
/**
 * for debug purposes - prints the input info
 */
void printInputs();
void update(int currentTime);
};  // namespace controls

// Serial.print("Button one: ");
// Serial.println(digitalRead(BUTTON_ONE));
// Serial.print("Button two: ");
// Serial.println(digitalRead(BUTTON_TWO));

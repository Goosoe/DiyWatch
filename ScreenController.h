/**
* @file ScreenController.h
* @author Goosoe
* @brief This header has an API to control all the displays for the clock
* @copyright Copyright (c) 2022
*
*/

#pragma once
#include <stdint.h>
#include "Util.h"

namespace screenController {
const uint8_t MAX_EDITABLE_FIELDS = 2;  //TODO: update when adding more displays

void setup();

void update(const int currentTime, const stateUtil::MODE mode);

void setEditableField(const uint8_t field);

void drawTime(const uint8_t* timeArr);

void resetBlink();
};  // namespace screenController
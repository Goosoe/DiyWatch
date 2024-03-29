
#include "Controls.h"

#include <Arduino.h>

namespace controls {

const uint8_t BUTTON_ONE = 11;
const uint8_t BUTTON_TWO = 12;

const uint16_t REFRESH = 250;  // updates every REFRESH ms
const float UPDATE_TIME = 1000 / REFRESH;
const float LONG_PRESS_TIME = 750;

int lastUpdate = 0;       // time in ms
int b1PressTimer = 0;  // 0 = off
int b2PressTimer = 0;  // 0 = off
uint8_t b1LastState = 0;  // 0 = off
uint8_t b2LastState = 0;  // 0 = off
bool b1HoldLock = false;
bool b2HoldLock = false;

void setup() {
    pinMode(BUTTON_ONE, INPUT);
    pinMode(BUTTON_ONE, INPUT);
}


//TODO: remove prints
void update(void(*observer)(COMMAND)) {
    uint32_t time = millis();
    if (time < lastUpdate) {      // Saves from the time eventual overflow
        lastUpdate = time;
    }

    uint32_t timePassed = time - lastUpdate;
    bool isUpdated = false;
    bool holdLock = false;
    COMMAND comm = COMMAND::NONE;
    if (timePassed < UPDATE_TIME) {
        return;
    }
    uint8_t state = digitalRead(BUTTON_ONE);

    if (!b1HoldLock && b1LastState == 1 && state == 1) {    //if the button is being pressed (Long press verification)
        b1PressTimer += timePassed;
        if (b1PressTimer >= LONG_PRESS_TIME) {
            b1HoldLock = true;
            comm = COMMAND::B1_HOLD;
            isUpdated = true;
        }
    }
    else if (b1LastState == 1 && state == 0) {    // button press
        if (!b1HoldLock) {
            comm = COMMAND::B1_PRESS;
            isUpdated = true;
        }
        b1HoldLock = false;
        b1PressTimer = 0;
    }
    b1LastState = state;
    state = digitalRead(BUTTON_TWO);

    if (!b2HoldLock && b2LastState == 1 && state == 1) {    //if the button is being pressed (Long press verification)
        b2PressTimer += timePassed;
        if (b2PressTimer >= LONG_PRESS_TIME) {
            comm = COMMAND::B2_HOLD;
            b2HoldLock = true;
            isUpdated = true;
        }
    }
    else if (b2LastState == 1 && state == 0) {    // button press
        if (!b2HoldLock) {
            comm = COMMAND::B2_PRESS;
            isUpdated = true;
        }
        b2HoldLock = false;
        b2PressTimer = 0;
    }
    b2LastState = state;
    lastUpdate = time;

    if (isUpdated) {
        observer(comm);
    }
}
};  // namespace controls

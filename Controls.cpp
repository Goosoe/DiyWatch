
#include "Controls.h"

#include <Arduino.h>

namespace controls {

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
void update(int currentTime, void(*observer)(COMMAND)) {
    if(currentTime <= lastUpdate){      // Saves from the currentTime eventual overflow
        lastUpdate = currentTime;
    }

    uint16_t timePassed = currentTime - lastUpdate;
    bool isUpdated = false;
    bool holdLock = false;
    COMMAND comm = COMMAND::NONE;
    if (timePassed < UPDATE_TIME) {
        return;
    }
    uint8_t state = digitalRead(BUTTON_ONE);

    if (!b1HoldLock && b1LastState == 1 && state == 1) {    //if the button is being pressed (Long press verification)
        b1PressTimer += timePassed;
        if(b1PressTimer >= LONG_PRESS_TIME){
            b1HoldLock = true;
            comm = COMMAND::B1_HOLD;
            isUpdated = true;
        }
    }
    else if(b1LastState == 1 && state == 0){    // button press
         if(!b1HoldLock){ 
            comm = COMMAND::B1_PRESS;
            isUpdated = true;
        }
        b1HoldLock = false;
        b1PressTimer = 0;
    }
    b1LastState = state;
    state = digitalRead(BUTTON_TWO);

    if (!b2HoldLock && b2LastState == 1 && state == 1 ) {    //if the button is being pressed (Long press verification)
        b2PressTimer += timePassed;
        if(b2PressTimer >= LONG_PRESS_TIME){
            comm = COMMAND::B2_HOLD;
            b2HoldLock = true;
            isUpdated = true;
        }
    }
    else if(b2LastState == 1 && state == 0){    // button press
         if(!b2HoldLock){ 
            comm = COMMAND::B2_PRESS;
            isUpdated = true;
        }
        b2HoldLock = false;
        b2PressTimer = 0;
    }
    b2LastState = state;
    lastUpdate = currentTime;

    if(isUpdated){
        observer(comm);
    }
    // getInput(); //TODO: DEBUG remove after testing
}
};  // namespace controls

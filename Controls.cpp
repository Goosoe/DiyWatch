
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

COMMAND_LIST commandList = COMMAND_LIST{
    COMMAND::NONE,
    COMMAND::NONE
};

void setup() {
    pinMode(BUTTON_ONE, INPUT);
    pinMode(BUTTON_ONE, INPUT);
}


//TODO: remove prints
void update(int currentTime, void(*observer)(COMMAND_LIST)) {
    uint16_t timePassed = currentTime - lastUpdate;
    bool isUpdated = false;
    if (timePassed < UPDATE_TIME) {
        return;
    }
    uint8_t state = digitalRead(BUTTON_ONE);

    if (b1LastState == 1 && state == 1 && !b1HoldLock) {    //if the button is being pressed (Long press verification)
        b1PressTimer += timePassed;
        if(b1PressTimer >= LONG_PRESS_TIME){
            commandList.b1 = COMMAND::B1_HOLD;
            Serial.print("Button 1:");
            Serial.println(commandList.b1);
            b1HoldLock = true;
            isUpdated = true;
        }
    }
    else if(b1LastState == 1 && state == 0){
         if(!b1HoldLock){ // means it was a press
            commandList.b1 = COMMAND::B1_PRESS;
            Serial.print("Button 1:");
            Serial.println(commandList.b1);
            isUpdated = true;
        }
        b1HoldLock = false;
        b1PressTimer = 0;
    }

    b1LastState = state;
    state = digitalRead(BUTTON_TWO);

    if (b2LastState == 1 && state == 1 && !b2HoldLock) {    //if the button is being pressed (Long press verification)
        b2PressTimer += timePassed;
        if(b2PressTimer >= LONG_PRESS_TIME){
            commandList.b2 = COMMAND::B2_HOLD;
            Serial.print("Button 2:");
            Serial.println(commandList.b2);
            b2HoldLock = true;
            isUpdated = true;
        }
    }
    else if(b2LastState == 1 && state == 0){
         if(!b2HoldLock){ // means it was a press
            commandList.b2 = COMMAND::B2_PRESS;
            Serial.print("Button 2:");
            Serial.println(commandList.b2);
            isUpdated = true;
        }
        b2HoldLock = false;
        b1PressTimer = 0;
    }
    b2LastState = state;
    lastUpdate = currentTime;
    if(isUpdated){
        observer(commandList);
    }
    // getInput(); //TODO: DEBUG remove after testing
}

// COMMAND_LIST getInput() {
//     COMMAND_LIST cl = COMMAND_LIST{
//         commandList.b1,
//         commandList.b2};
//     commandList.b1 = COMMAND::NONE;
//     commandList.b2 = COMMAND::NONE;
//     return cl;
// }
};  // namespace controls

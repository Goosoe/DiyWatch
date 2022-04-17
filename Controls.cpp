
#include "Controls.h"

#include <Arduino.h>

namespace controls {

int lastUpdate = 0;       // time in ms
uint8_t b1LastState = 0;  // 0 = off
uint8_t b2LastState = 0;  // 0 = off
COMMAND b1Command = COMMAND::NONE;
COMMAND b2Command = COMMAND::NONE;

void setup() {
    pinMode(BUTTON_ONE, INPUT);
    pinMode(BUTTON_ONE, INPUT);
}

// void printInputs() {  // TODO: REMOVE AFTER DEBUG
//     COMMAND_LIST commandList = getInput();
//     Serial.print("Button one: ");
//     Serial.println(commandList.b1);
//     Serial.print("Button two: ");
//     Serial.println(commandList.b2);
// }

void update(int currentTime) {
    if (currentTime - lastUpdate >= UPDATE_TIME) {
        uint8_t state = digitalRead(BUTTON_ONE);
        if (b1LastState != state) {
            b1LastState = state;
            if (!b1LastState) {
                b1Command = COMMAND::B1_PRESS;
                Serial.println("Button 1 pressed");
            }
        }

        state = digitalRead(BUTTON_TWO);
        if (b2LastState != state) {
            b2LastState = state;
            if (!b2LastState) {
                b2Command = COMMAND::B2_PRESS;
                Serial.println("Button 2 pressed");
            }
        }
        lastUpdate = currentTime;
    }
}
COMMAND_LIST getInput() {
    COMMAND_LIST commandList = COMMAND_LIST{
        b1Command,
        b2Command};
    b1Command = COMMAND::NONE;
    b2Command = COMMAND::NONE;
    return commandList;
}

};  // namespace controls

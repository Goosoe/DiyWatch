
#include "Controls.h"

#include <Arduino.h>

namespace controls {

int lastUpdate = 0;  // time in ms

void setup() {
    pinMode(BUTTON_ONE, INPUT);
    pinMode(BUTTON_ONE, INPUT);
}

void printInputs() {  // TODO: REMOVE AFTER DEBUG
    Serial.print("Button one: ");
    Serial.println(digitalRead(BUTTON_ONE));
    Serial.print("Button two: ");
    Serial.println(digitalRead(BUTTON_TWO));
}

void update(int currentTime) {
    if (currentTime - lastUpdate >= UPDATE_TIME) {
        // printInputs();
        lastUpdate = currentTime;
    }
}
};  // namespace controls

#include "Actuators.h"

#include <Arduino.h>
#include <stdint.h>

namespace actuators {
const uint16_t REFRESH = 2;  // nr of updates per sec
const float UPDATE_TIME = 1000 / REFRESH;
const uint8_t VIBRATOR = 4; // A2 port
uint8_t index = 0;

uint32_t time;
bool vibrate = false;
uint32_t lastUpdate = 0;

void setup() {
    pinMode(VIBRATOR, OUTPUT);
}

void updateVibrator() {
    if (!vibrate) {
        return;
    }
    time = millis();
    if (time < lastUpdate) {  // Saves from the time eventual overflow
        lastUpdate = time;
    }
    if (time - lastUpdate < UPDATE_TIME) {
        return;
    }
    digitalWrite(VIBRATOR, index == 0 ? 255 : 0); //TODO: use buzzVal array
    index = (index + 1) % 2;
    lastUpdate = time;
}

void update() {
    updateVibrator();
}

void setVibrator(const bool on) {
    vibrate = on;
    if (!on) {
        digitalWrite(VIBRATOR, LOW);
    }
}
}

#include "Controls.h"
#include "RTC.h"
#include "TimeDisplay.h"

const uint8_t SIZE = 6;
uint8_t timeArr[SIZE] = {0};

void setup() {
    timeDisplay::setup();
    mcpRtc::setup();
    // controls::setup();
    Serial.begin(9600);  // TODO: DEBUG PURPOSE. DELETE AFTERWARDS
    // Serial.print(getnum());
}

void loop() {
    updateTimers();
    mcpRtc::getTime(timeArr, SIZE);
    timeDisplay::drawNumbers(timeArr);
}

void updateTimers() {
    int currentTime = millis();
    timeDisplay::update(currentTime);  // TimeDisplay update
}

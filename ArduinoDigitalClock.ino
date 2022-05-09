#include "Controls.h"
#include "RTC.h"
#include "TimeDisplay.h"

const uint8_t SIZE = 6;
uint8_t timeArr[SIZE] = {0};

void setup() {
    timeDisplay::setup();
    mcpRtc::setup();
    controls::setup();
    Serial.begin(9600);  // TODO: DEBUG PURPOSE. DELETE AFTERWARDS
}

void loop() {
    updateTimers();
    mcpRtc::getTime(timeArr, SIZE);
    timeDisplay::drawNumbers(timeArr);
    
}

void updateTimers() {
    int currentTime = millis();
    timeDisplay::update(currentTime);  // TimeDisplay update
    controls::update(currentTime, &test);
}

void test(controls::COMMAND comm){
    Serial.print("===\nButton command:");
    Serial.println(comm);
    Serial.println("===");
}
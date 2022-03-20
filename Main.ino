#include "Controls.h"
#include "DisplaySR.h"
#include "RTC.h"

void setup() {
    display::setup();
    rtc::setup();
    controls::setup();
    Serial.begin(9600);  // TODO: DEBUG PURPOSE. DELETE AFTERWARDS
    // Serial.print(getnum());
}

void loop() {
    uint8_t size = 6;
    uint8_t timeArr[size] = {0};
    rtc::getTime(timeArr, size);
    display::drawNumbers(timeArr, size, true);
}
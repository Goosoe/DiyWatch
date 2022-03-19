

void setup() {
    displaySetup();
    rtcSetup();

    Serial.begin(9600);  // TODO: DEBUG PURPOSE. DELETE AFTERWARDS
}

void loop() {
    uint8_t size = 6;
    uint8_t timeArr[size] = {0};
    getTime(timeArr, size);
    drawNumbers(timeArr, size, clkDiv);
}
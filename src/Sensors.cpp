#include "Sensors.h"
#include "Arduino.h"    //TODO: remove after debug
#include <math.h>  
namespace sensors {

const uint8_t TEMP_CALIBRATION_OFFSET = 10;
const uint8_t TEMP_ARR_SIZE = 5;
const uint8_t TEMP_SENSOR = 17; //port A3
const uint16_t UPDATE_TIME = 60000; // ms TODO: change to a reasonable value

/*Struct and function declarations*/
struct {
    int8_t avgTemp[TEMP_ARR_SIZE] = { 0 };
    uint8_t iter = 0;
} tempData;

uint8_t readTempSensor();

int8_t currentTemp = 0;
uint32_t lastUpdate = 0;  // time in ms

void setup() {
    for (uint8_t i = 0; i < TEMP_ARR_SIZE; i++) {
        tempData.avgTemp[i] = readTempSensor();
    }
}

void update() {
    const uint32_t time = millis();
    if (time <= lastUpdate) {  // Saves from the eventual time overflow
        lastUpdate = time;
    }
    if (time - lastUpdate < UPDATE_TIME) {
        return;
    }
    tempData.avgTemp[tempData.iter] = readTempSensor();
    tempData.iter = (tempData.iter + 1) % TEMP_ARR_SIZE;
    lastUpdate = time;
}

uint8_t readTempSensor() {
    int reading = analogRead(TEMP_SENSOR);
    float voltage = reading * (4750 / 1024.0f);  // voltage being sent is around 4.75V and current is ~1.02 mA
    currentTemp = round(voltage / 10 - 273.15f - TEMP_CALIBRATION_OFFSET); //convert from K to C and remove 10 to counter the offset
    return currentTemp;
}

uint8_t getTemp() {
    int16_t total = 0;
    for (uint8_t i = 0; i < TEMP_ARR_SIZE; i++) {
        total += tempData.avgTemp[i];
    }
    return round(total / TEMP_ARR_SIZE);
}
}; //namespace sensors
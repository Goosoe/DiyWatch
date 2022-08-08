#include "ScreenController.h"
#include <Arduino.h>
#include "SevenSegment.h"
#include "LedArray.h"
#include "../Util.h"

namespace screenController {
bool blink = false;
bool blinkVal = false;

const uint16_t BLINK_TIME = 600;

uint8_t editableField = 0;  //needed to know when to switch the blink between screens
uint32_t lastBlink = 0;   // time in ms

void setup() {
    svnSeg::setup();
    ledArr::setup();
}

void update() { //TODO: state mode must be specific to different modules
    if (blink) {
        uint32_t time = millis();
        if (time < lastBlink) {  // Saves from the time eventual overflow
            lastBlink = time;
        }
        if (time - lastBlink > BLINK_TIME) {

            if (editableField < SEVEN_SEG_FIELDS) {   //0 = hours, 1 = minutes //TODO: magic numbers
                svnSeg::setPartialScreenPower(blinkVal);
            }
            else {
                ledArr::setScreenPower(blinkVal);
            }
            blinkVal = !blinkVal;
            lastBlink = time;
        }
    }
    svnSeg::update();
    ledArr::update();
}

/**
 * @brief Set the Editable Field value
 * @param field
 */
void setEditableField(const uint8_t field) {
    editableField = field;
    blinkVal = true;
    if (editableField < SEVEN_SEG_FIELDS) {   //0 = hours, 1 = minutes //TODO: magic numbers
        ledArr::setScreenPower(true);
        svnSeg::setEditableField(editableField);
    }
    else {
        svnSeg::setPartialScreenPower(true);
        svnSeg::setEditableField(0);
        ledArr::setScreenPower(false);
    }
}

void resetEditMode() {
    setEditableField(0);
    svnSeg::setPartialScreenPower(true);
    blink = false;
}

uint8_t incrementEditField(stateUtil::STATE state) {
    uint8_t maxFields = MAX_EDITABLE_FIELDS_TIME;
    if (stateUtil::ALARM == state) {
        maxFields = SEVEN_SEG_FIELDS;
    }
    uint8_t nextField = (editableField + 1) % maxFields; //TODO: change this when adding different editable fields
    setEditableField(nextField);
    lastBlink = millis();
    return nextField;
}

void SSDraw(const uint8_t* timeArr) {
    svnSeg::setNumbers(timeArr);
}


void LASendToBuffer(const char* str, const bool reset) {
    ledArr::sendToBuffer(str, reset);
}

void setBlink(const bool val) {
    blink = val;
}

void setBlinkVal(const bool val) {
    if (editableField < SEVEN_SEG_FIELDS) {   //0 = hours, 1 = minutes 
        svnSeg::setPartialScreenPower(val);
    }
    else {
        ledArr::setScreenPower(val);
    }
    lastBlink = millis();
}

uint8_t getEditField() {
    return editableField;
}

}; // namespace screenController

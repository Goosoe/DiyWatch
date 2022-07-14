#include "ScreenController.h"
#include <Arduino.h>
#include "SevenSegment.h"
#include "LedArray.h"
#include "../Util.h"

namespace screenController {
bool blink = false;
uint8_t editableField = 0;  //needed to know when to switch the blink between screens

void setup() {
    svnSeg::setup();
    ledArr::setup();
}

void update() { //TODO: state mode must be specific to different modules
    svnSeg::update();
    ledArr::update();
}

/**
 * @brief Set the Editable Field value
 * @param field
 */
void setEditableField(const uint8_t field) {
    editableField = field;
    if (editableField < 2) {   //0 = hours, 1 = minutes //TODO: magic numbers
        svnSeg::setEditableField(min(editableField, MAX_EDITABLE_FIELDS));
    }
    else {
        if (blink) {
            svnSeg::setBlink(false);
            // ledArr::setEditableField(min(editableField, MAX_EDITABLE_FIELDS));
        }
        //ledArr::setBlink(true);

    }
}

void resetEditField() {
    setEditableField(0);
}
void incrementEditField() {
    setEditableField((editableField + 1) % MAX_EDITABLE_FIELDS);
}

void SSDraw(const uint8_t* timeArr) {
    svnSeg::drawNumbers(timeArr);
}


void LASendToBuffer(const char* str, const bool reset) {
    ledArr::sendToBuffer(str, reset);
}

void setBlink(const bool val) {
    blink = val;
    if (editableField < 2) {   //0 = hours, 1 = minutes //TODO: magic numbers
        svnSeg::setBlink(blink);
    }
    else {
        // ledArr::setBlink(on);
    }
}

uint8_t getEditField() {
    return editableField;
}

}; // namespace screenController

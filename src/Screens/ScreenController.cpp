#include "ScreenController.h"
#include "SevenSegment.h"
#include "LedArray.h"
#include "../Util.h"

namespace screenController {

void setup() {
    timeDisplay::setup();
    ledArray::setup();
}

void update(const uint32_t time, const stateUtil::MODE mode) { //TODO: state mode must be specific to different modules
    timeDisplay::update(time, mode);
    ledArray::update(time, mode);
}

/**
 * @brief Set the Editable Field object
 * @param field
 */
void setEditableField(const uint8_t field) {
    if (field < 2) {   //0 = hours, 1 = minutes
        timeDisplay::setEditableField(field);
    }
}

void drawTime(const uint8_t* timeArr) {
    timeDisplay::drawNumbers(timeArr);
}

void resetBlink(const uint16_t time) {
    timeDisplay::setBlink(false, time);
}

} // namespace screenController

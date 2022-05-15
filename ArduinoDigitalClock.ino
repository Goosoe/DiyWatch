#include "Controls.h"
#include "RTC.h"
#include "ScreenController.h"
#include "Util.h"

const uint8_t SIZE = 6;
uint8_t timeArr[SIZE] = {0};

namespace stateController {

uint8_t state, mode = 0;
uint8_t currentEditField = -1;

/**
 * @brief resets all the variables used in the edit mode so it can start properly next time edit mode is entered in
 */
void resetEditData(){
    currentEditField = -1;
}
void evalCommand(controls::COMMAND comm) {
    // Serial.print("===\nButton command:");
    // Serial.println(comm);
    // Serial.println("===");

    switch (comm) {
        case controls::COMMAND::B1_PRESS:
            if ((int)stateUtil::MODE::READ == mode) {
                resetEditData();
                // TODO: uncomment when we want to switch between modes
                //     state += 1 % (STATE::ALARM + 1); //USE LAST STATE OF THE ENUM
                //     Serial.print("===\nNew State:");
                //     Serial.println(state);
                //     Serial.println("===");
            } else if ((int)stateUtil::MODE::EDIT == mode && (int)stateUtil::STATE::TIME == state) {
                currentEditField = (currentEditField + 1) % screenController::MAX_EDITABLE_FIELDS; 
                Serial.println(currentEditField);
                screenController::setEditableField(currentEditField);
                break;
            }
        case controls::COMMAND::B1_HOLD:
            mode = (mode + 1) % ((int)stateUtil::MODE::EDIT + 1);  // USE LAST MODE OF THE ENUM
            // Serial.print("===\nNew Mode:");
            // Serial.println(mode);
            // Serial.println("===");
            break;
        case controls::COMMAND::B2_PRESS:
            // if(mode == MODE::READ && state == STATE::TIME){

            // }
            // else if(mode == MODE::EDIT && state == STATE::TIME){

            // }
            break;
        default:
            break;
    }
}
};  //  namespace stateController

void setup() {
    screenController::setup();
    mcpRtc::setup();
    controls::setup();
    Serial.begin(9600);  // TODO: DEBUG PURPOSE. DELETE AFTERWARDS
}

void loop() {
    updateComponents();
    mcpRtc::getTime(timeArr, SIZE);
    screenController::drawTime(timeArr);
}

void updateComponents() {
    int currentTime = millis();
    screenController::update(currentTime, static_cast<stateUtil::MODE>(stateController::mode));  // TimeDisplay update
    controls::update(currentTime, &stateController::evalCommand);
}
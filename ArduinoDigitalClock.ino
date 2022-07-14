#include "src/Controls.h"
#include "src/RTC.h"
#include "src/Screens/ScreenController.h"
#include "src/Util.h"
#include "src/Sensors.h"
#include <string.h>

const uint8_t SIZE = 6;
uint8_t timeArr[SIZE] = { 0 };

namespace stateController {

uint8_t state, mode, currentEditField = 0;

bool switchState = false;
// uint8_t currentEditField = 0;

/**
 * @brief resets all the variables used in the edit mode so it can start properly next time edit mode is entered in
 */
void resetEditData() {
    currentEditField = screenController::setEditableField(0);
}

/**
 * @brief Called from the responsible Controller function.
 * It evaluates a COMMAND and acts on the state machine
 * @param comm command received
 */
void evalCommand(controls::COMMAND comm) {
    switch (comm) {
    case controls::COMMAND::B1_PRESS:
        if (stateUtil::MODE::READ == mode) {
            state = (state + 1) % (stateUtil::STATE::ALARM + 1);
            switchState = true;
        }
        else if (stateUtil::MODE::EDIT == mode) {
            if (stateUtil::STATE::TIME == state) {
                currentEditField = screenController::incrementEditField();
                screenController::setBlink(true);
            }
        }
        break;

    case controls::COMMAND::B1_HOLD:
        if (stateUtil::MODE::READ == mode) {
            mode = stateUtil::MODE::EDIT;
            if (stateUtil::STATE::TIME == state) {
                resetEditData();
                screenController::setBlink(true);
                //TODO: set mode
            }
        }
        else if (stateUtil::MODE::EDIT == mode) {
            mode = stateUtil::MODE::READ;
            resetEditData();
            screenController::setBlink(false);
        }
        break;

    case controls::COMMAND::B2_PRESS:
        if (stateUtil::STATE::TIME == state) {
            if (stateUtil::MODE::READ == mode) {
                //TODO:
            }
            else if (stateUtil::MODE::EDIT == mode) {
                switch (currentEditField) {
                case 0:
                    mcpRtc::addHour();
                    screenController::setBlink(true);   //to update blink timer
                    break;
                case 1:
                    mcpRtc::addMinute();
                    screenController::setBlink(true);   //to update blink timer
                default:
                    break;
                }
            }
        }
        break;

    case controls::COMMAND::B2_HOLD:
        if (stateUtil::STATE::TIME == state) {
            if (stateUtil::MODE::READ == mode) {
                //TODO:
            }
            else if (stateUtil::MODE::EDIT == mode) {   //TODO: thread addhour & addminute?
                switch (currentEditField) {     //TODO: Hold button is the same as press right nonw
                case 0: // edit hour field
                    mcpRtc::addHour();
                    break;
                case 1:
                    mcpRtc::addMinute();
                default:
                    break;
                }
            }
        }
        break;
    default:
        break;
    }
}
}; //  namespace stateController

/**
 * @brief Main setup
 */
void setup() {
    screenController::setup();
    mcpRtc::setup();
    controls::setup();
    sensors::setup();
    Serial.begin(9600); // TODO: DEBUG PURPOSE. DELETE AFTERWARDS
}

/**
 * @brief Main loop
 */
void loop() {
    updateComponents();
    //TODO: add in the state machine? or make these functions be called over time
    mcpRtc::getTime(timeArr, SIZE); //TODO: does not need to be called every iteration. 10 times per second maybe?  
    screenController::SSDraw(timeArr);
    // screenController::LASendToBuffer("123456789");

    //TODO: put in a function
    switch (stateController::state) {
    case stateUtil::STATE::TIME:
        screenController::LASendToBuffer("mon 21 22", stateController::switchState);
        break;
    case stateUtil::STATE::SENSORS:
        screenController::LASendToBuffer(String(sensors::getTemp()).c_str(), stateController::switchState);
        break;

    case stateUtil::STATE::CHRONOMETER:
        screenController::LASendToBuffer("345", stateController::switchState);
        break;

    case stateUtil::STATE::ALARM:
        screenController::LASendToBuffer("6789", stateController::switchState);
        break;

    default:
        break;
    }
    if (stateController::switchState) {
        stateController::switchState = false;
    }
    // screenController::drawLA("123");
    // sensors::getTemp(); //TODO: should be called every minute

}

/**
 * @brief Updates all the connected components
 */
void updateComponents() {
    screenController::update();
    controls::update(&stateController::evalCommand);
    sensors::update();
}
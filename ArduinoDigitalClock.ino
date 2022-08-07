#include "src/Controls.h"
#include "src/RTC.h"
#include "src/Screens/ScreenController.h"
#include "src/Util.h"
#include "src/Sensors.h"

const uint8_t SIZE = 6;
uint8_t timeArr[SIZE] = { 0 };
const uint8_t STARTING_YEAR = 20; //The year the clock displays + 1

namespace stateController {
const uint8_t DATE_SIZE = 13;
uint8_t state, mode = 0;
char date[DATE_SIZE] = { 0 };
bool updateLA = true;
bool alarmOn = false;
/**
 * @brief Resets all the blink information when going back to read mode
 *
 */
void resetBlink() {
    screenController::resetEditMode();
}

void prepareDate() {
    util::createDate(date, mcpRtc::getDate(), mcpRtc::getWeekDay(), mcpRtc::getMonth(), mcpRtc::getYear());
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

            updateLA = true;
        }
        else if (stateUtil::MODE::EDIT == mode) {
            if (stateUtil::STATE::TIME == state) {
                if (screenController::incrementEditField() < screenController::SEVEN_SEG_FIELDS) {
                    screenController::setBlinkVal(false);
                    screenController::LASendToBuffer(stateController::date, true);
                }
                else { // Time edit in Led Array
                    updateLA = true;
                }
            }
            if (stateUtil::STATE::ALARM == state) {
                if (screenController::incrementEditField(stateUtil::STATE::ALARM)) {
                    screenController::setBlinkVal(false);
                    screenController::LASendToBuffer("", true);
                }
            }
        }
        // todo: screenController::incrementEditField(stateUtil::ALARM);
        break;

    case controls::COMMAND::B1_HOLD:
        if (stateUtil::MODE::READ == mode) {
            if (stateUtil::STATE::TIME == state || stateUtil::STATE::ALARM == state) {
                mode = stateUtil::MODE::EDIT;
                screenController::setBlink(true);
                //TODO: set mode
            }
        }
        else if (stateUtil::MODE::EDIT == mode) {
            mode = stateUtil::MODE::READ;
            resetBlink();
            if (stateUtil::STATE::TIME == state) {
                screenController::LASendToBuffer(stateController::date, true);
            }
            else if (stateUtil::STATE::ALARM == state) {
                screenController::setBlink(false);
            }
        }
        break;

    case controls::COMMAND::B2_PRESS:
        if (stateUtil::STATE::TIME == state) {
            if (stateUtil::MODE::READ == mode) {
                //TODO:
            }
            else if (stateUtil::MODE::EDIT == mode) {
                if (screenController::getEditField() >= screenController::SEVEN_SEG_FIELDS) {
                    updateLA = true;
                }
                switch (screenController::getEditField()) {
                case 0: // edit hour field
                    mcpRtc::addHour();
                    break;
                case 1:
                    mcpRtc::addMinute();
                    break;
                case 2:
                    mcpRtc::addDate();
                    break;
                case 3:
                    mcpRtc::addWeekDay();
                    break;
                case 4:
                    mcpRtc::addMonth();
                    break;
                case 5:
                    mcpRtc::addYear();
                    break;
                default:
                    break;
                }
                screenController::setBlinkVal(true);
                prepareDate();
            }
        }
        else if (stateUtil::STATE::ALARM == state) {
            if (stateUtil::MODE::READ == mode) {
                alarmOn = !alarmOn;
            }
            else if (stateUtil::MODE::EDIT == mode) {
                switch (screenController::getEditField()) {
                case 0: // edit hour field
                    mcpRtc::addAlrHour();
                    break;
                case 1:
                    mcpRtc::addAlrMinute();
                    break;
                default:
                    break;
                }
                screenController::setBlinkVal(true);
            }
        }
        break;
    case controls::COMMAND::B2_HOLD:
        if (stateUtil::STATE::TIME == state) {
            if (stateUtil::MODE::READ == mode) {
                //TODO:
            }
            break;
        }
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
    stateController::prepareDate();
    Serial.begin(9600); // TODO: DEBUG PURPOSE. DELETE AFTERWARDS
}

/**
 * @brief Main loop
 */
void loop() {
    updateComponents();
    //    mcpRtc::getTime(timeArr, SIZE); //TODO: does not need to be called every iteration. 10 times per second maybe?  
    //    screenController::SSDraw(timeArr);
        // screenController::LASendToBuffer("123456789");
        //TODO: put in a function
    switch (stateController::state) {
    case stateUtil::STATE::TIME: {
        mcpRtc::getTime(timeArr, SIZE); //TODO: does not need to be called every iteration. 10 times per second maybe?  
        screenController::SSDraw(timeArr);
        if (stateUtil::MODE::READ == stateController::mode) {
            //TODO: dont update date every loop.
            screenController::LASendToBuffer(stateController::date, stateController::updateLA);
        }
        else {
            char LAText[3] = { 0 };
            uint8_t i = 0;
            switch (screenController::getEditField()) {
            case 2:
                util::numToChar(mcpRtc::getDate(), LAText, i);
                screenController::LASendToBuffer(LAText, stateController::updateLA);
                break;
            case 3:
                util::numToDayWeek(mcpRtc::getWeekDay(), LAText, i);
                screenController::LASendToBuffer(LAText, stateController::updateLA);
                break;
            case 4:
                util::numToMonth(mcpRtc::getMonth(), LAText, i);
                screenController::LASendToBuffer(LAText, stateController::updateLA);
                break;
            case 5:
                util::numToChar(mcpRtc::getYear(), LAText, i);
                screenController::LASendToBuffer(LAText, stateController::updateLA);
                break;
            default:
                break;
            }
        }
        break;
    }
    case stateUtil::STATE::SENSORS:
        mcpRtc::getTime(timeArr, SIZE); //TODO: does not need to be called every iteration. 10 times per second maybe?  
        screenController::SSDraw(timeArr);
        char temp[4];  // space for a possible negative value and /0 character
        itoa(sensors::getTemp(), temp, 10);
        screenController::LASendToBuffer(temp, stateController::updateLA);
        break;
    case stateUtil::STATE::ALARM:
        //TODO: implement
        if (stateController::alarmOn) {
            screenController::LASendToBuffer("ON", stateController::updateLA);
        }
        else {
            screenController::LASendToBuffer("OFF", stateController::updateLA);
        }
        uint8_t alrmTime[4];
        mcpRtc::getAlrTime(alrmTime);
        screenController::SSDraw(alrmTime);
        break;
    default:
        break;
    }
    if (stateController::updateLA) {
        stateController::updateLA = false;
    }
}

/**
 * @brief Updates all the connected components
 */
void updateComponents() {
    screenController::update();
    controls::update(&stateController::evalCommand);
    sensors::update();
}

#include "Util.h"
#include "Arduino.h"

namespace util {

const uint8_t DEFAULT_SIZE = 3;
void numToDayWeek(const uint8_t val, char* out, uint8_t& index) {// TODO: not good return

    const char* day;
    switch (val) {
    case 1:
        day = "MON";
        break;
    case 2:
        day = "TUE";
        break;
    case 3:
        day = "WED";
        break;
    case 4:
        day = "THU";
        break;
    case 5:
        day = "FRI";
        break;
    case 6:
        day = "SAT";
        break;
    case 7:
        day = "SUN";
        break;
    default:
        break;
    }

    for (int i = 0; i < DEFAULT_SIZE; i++) {
        out[index + i] = day[i];
    }

    index += DEFAULT_SIZE;
}
void numToMonth(uint8_t val, char* out, uint8_t& index) { // TODO: not good
    const char* month;
    switch (val) {
    case 1:
        month = "JAN";
        break;
    case 2:
        month = "FEB";
        break;
    case 3:
        month = "MAR";
        break;
    case 4:
        month = "APR";
        break;
    case 5:
        month = "MAY";
        break;
    case 6:
        month = "JUN";
        break;
    case 7:
        month = "JUL";
        break;
    case 8:
        month = "AUG";
        break;
    case 9:
        month = "SEP";
        break;
    case 10:
        month = "OCT";
        break;
    case 11:
        month = "NOV";
        break;
    case 12:
        month = "DEC";
        break;
    default:
        break;
    }

    for (uint8_t i = 0; i < DEFAULT_SIZE; i++) {
        out[index + i] = month[i];
    }
    index += DEFAULT_SIZE;
}
void numToChar(uint16_t val, char* out, uint8_t& index) {
    const uint8_t YEAR_SIZE = 2;
    for (int8_t i = YEAR_SIZE - 1; i >= 0; i--) {
        out[index + i] = val % 10 + '0';
        val /= 10;
    }
    index += YEAR_SIZE;
}

void createDate(char* dateArr, const uint8_t day, const uint8_t weekDay, const uint8_t month, const uint16_t year) {
    uint8_t index = 0;
    numToDayWeek(day, dateArr, index);
    numToDayWeek(weekDay, dateArr, index);
    numToMonth(month, dateArr, index);
    numToChar(year, dateArr, index);
}

}; // namespace util
/**
 * @file Util.h
 * @author Goosoe
 * @brief This file has all enums and functions required for multiple files
 */
#pragma once
namespace stateUtil {
enum MODE {
    READ,
    EDIT

};

enum STATE {
    TIME,
    SENSORS,
    CHRONOMETER,
    ALARM
};
}; // namespace stateUtil
// # pragma once
// namespace util {
// char* numToDayWeek(uint8_t val) {
//     char day[3] = { " " };
//     switch (val) {
//     case 1:
//         return strcpy(day, "MON");
//     case 2:
//         return strcpy(day, "TUE");
//     case 3:
//         return strcpy(day, "WED");
//     case 4:
//         return strcpy(day, "THU");
//     case 5:
//         return strcpy(day, "FRI");
//     case 6:
//         return strcpy(day, "SAT");
//     case 7:
//         return strcpy(day, "SUN");
//     default:
//         return day;
//     }
// }
// }; // namespace util
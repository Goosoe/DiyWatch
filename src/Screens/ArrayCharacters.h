/**
 * @file ArrayCharacters.h
 * @brief Has the array representation of any relevant character needed to print on the LED Array
 * @version 0.1
 * @date 2022-07-11
 *
 */
#include <stdint.h>

namespace arrayChar {

const uint8_t SIZE_OF_CHARS = 3; //size of the character in the display
const uint16_t SPACE_BETWEEN_CHARS = 0; //byteCode to replicate a line between characters in the display

struct CharArr {
    uint8_t size;
    const int* vals;
};

CharArr toLEDChar(const char c);
} // namespace arrayChar






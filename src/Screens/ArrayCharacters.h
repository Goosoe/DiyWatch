/**
 * @file ArrayCharacters.h
 * @brief Has the array representation of any relevant character needed to print on the LED Array
 */
#include <stdint.h>

namespace arrayChar {

const uint8_t SIZE_OF_CHARS = 3; //size of the character in the display
const uint16_t SPACE_BETWEEN_CHARS = 0; //byteCode to replicate a line between characters in the display

/**
 * @brief Information about the mapped char
 *
 */
struct CharArr {
    uint8_t size;
    const int* vals;
};

/**
 * @brief Takes a char and returns the byte map to represent in Led Array
 *
 * @param c - char to map
 * @return CharArr
 */
CharArr toLEDChar(const char c);
} // namespace arrayChar






#include "ArrayCharacters.h"
#include <Arduino.h>

namespace arrayChar {

const int ZERO[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0100010000000000, 0b0111110000000000 };
const int ONE[SIZE_OF_CHARS] = { 0, 0, 0b0111110000000000 };
const int TWO[SIZE_OF_CHARS] = { 0b0111010000000000, 0b0101010000000000, 0b0101110000000000 };
const int THREE[SIZE_OF_CHARS] = { 0b0101010000000000, 0b0101010000000000, 0b0111110000000000 };
const int FOUR[SIZE_OF_CHARS] = { 0b0001111000000000, 0b0001000000000000, 0b0111110000000000 };
const int FIVE[SIZE_OF_CHARS] = { 0b0101110000000000, 0b0101010000000000, 0b0111010000000000 };
const int SIX[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0101010000000000, 0b0111010000000000 };
const int SEVEN[SIZE_OF_CHARS] = { 0b0000010000000000, 0b0000010000000000, 0b0111110000000000 };
const int EIGHT[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0101010000000000, 0b0111110000000000 };
const int NINE[SIZE_OF_CHARS] = { 0b0001110000000000, 0b0001010000000000, 0b0111110000000000 };
const int SPACE[SIZE_OF_CHARS] = { 0 };

CharArr toLEDChar(const char c) {
    CharArr charArr;

    switch (c) {
    case '0':
        charArr = {
            SIZE_OF_CHARS,
            ZERO
        };
        break;
    case '1':
        charArr = {
            SIZE_OF_CHARS,
            ONE
        };
        break;
    case '2':
        charArr = {
            SIZE_OF_CHARS,
            TWO
        };
        break;
    case '3':
        charArr = {
            SIZE_OF_CHARS,
            THREE
        };
        break;
    case '4':
        charArr = {
            SIZE_OF_CHARS,
            FOUR
        };
        break;
    case '5':
        charArr = {
            SIZE_OF_CHARS,
            FIVE
        };
        break;
    case '6':
        charArr = {
            SIZE_OF_CHARS,
            SIX
        };
        break;
    case '7':
        charArr = {
            SIZE_OF_CHARS,
            SEVEN
        };
        break;
    case '8':
        charArr = {
            SIZE_OF_CHARS,
            EIGHT
        };
        break;
    case '9':
        charArr = {
            SIZE_OF_CHARS,
            NINE
        };
        break;
    default:
        charArr = {
            SIZE_OF_CHARS,
            SPACE
        };
        break;
    }
    return charArr;
}
} // namespace arrayChar

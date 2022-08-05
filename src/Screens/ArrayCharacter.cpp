#include "ArrayCharacters.h"
#include <Arduino.h>

namespace arrayChar {

const int ZERO[] = { 0b0111110000000000, 0b0100010000000000, 0b0111110000000000 };
const int ONE[] = { 0, 0b0111110000000000, 0 };;
const int TWO[] = { 0b0111010000000000, 0b0101010000000000, 0b0101110000000000 };
const int THREE[] = { 0b0101010000000000, 0b0101010000000000, 0b0111110000000000 };
const int FOUR[] = { 0b0001111000000000, 0b0001000000000000, 0b0111110000000000 };
const int FIVE[] = { 0b0101110000000000, 0b0101010000000000, 0b0111010000000000 };
const int SIX[] = { 0b0111110000000000, 0b0101010000000000, 0b0111010000000000 };
const int SEVEN[] = { 0b0000010000000000, 0b0000010000000000, 0b0111110000000000 };
const int EIGHT[] = { 0b0111110000000000, 0b0101010000000000, 0b0111110000000000 };
const int NINE[] = { 0b0101110000000000, 0b0101010000000000, 0b0111110000000000 };

const int A[] = { 0b0111100000000000, 0b0001010000000000, 0b0111100000000000 };
const int B[] = { 0b0111110000000000, 0b0101010000000000, 0b0110110000000000 };
const int C[] = { 0b0111110000000000, 0b0100010000000000, 0b0100010000000000 };
const int D[] = { 0b0111110000000000, 0b0100010000000000, 0b0011100000000000 };
const int E[] = { 0b0111110000000000, 0b0101010000000000, 0b0101010000000000 };
const int F[] = { 0b0111110000000000, 0b0001010000000000, 0b0001010000000000 };
const int H[] = { 0b0111110000000000, 0b0101010000000000, 0b0100010000000000 };
const int J[] = { 0b0010010000000000, 0b0100010000000000, 0b0111110000000000 };
const int L[] = { 0b0111110000000000, 0b0100000000000000, 0b0100000000000000 };
const int M[] = { 0b0111110000000000, 0b0000100000000000, 0b0111110000000000 };
const int N[] = { 0b0111100000000000, 0b0001000000000000, 0b0111100000000000 };
const int P[] = { 0b0111110000000000, 0b0001010000000000, 0b0001110000000000 };
const int R[] = { 0b0111110000000000, 0b0010010000000000, 0b0101110000000000 };
const int T[] = { 0b0000010000000000, 0b0111110000000000, 0b0000010000000000 };
const int U[] = { 0b0111110000000000, 0b0100000000000000, 0b0111110000000000 };
const int V[] = { 0b0011100000000000, 0b0100000000000000, 0b0011100000000000 };
const int W[] = { 0b0111110000000000, 0b0010000000000000, 0b0111110000000000 };
const int Y[] = { 0b0001100000000000, 0b0110000000000000, 0b0001100000000000 };

const int SPACE[SIZE_OF_CHARS] = { 0 };

CharArr toLEDChar(const char c) {
    CharArr charArr;

    switch (c) {
    case 'O':
    case '0':
        charArr = {
            SIZE_OF_CHARS,
            ZERO
        };
        break;
    case 'I':
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
    case 'S':
    case '5':
        charArr = {
            SIZE_OF_CHARS,
            FIVE
        };
        break;
    case 'G':
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
    case 'A':
        charArr = {
            SIZE_OF_CHARS,
            A
        };
        break;
    case 'B':
        charArr = {
            SIZE_OF_CHARS,
            B
        };
        break;
    case 'C':
        charArr = {
            SIZE_OF_CHARS,
            C
        };
        break;
    case 'D':
        charArr = {
            SIZE_OF_CHARS,
            D
        };
        break;
    case 'E':
        charArr = {
            SIZE_OF_CHARS,
            E
        };
        break;
    case 'F':
        charArr = {
            SIZE_OF_CHARS,
            F
        };
        break;
    case 'H':
        charArr = {
            SIZE_OF_CHARS,
            H
        };
        break;
    case 'J':
        charArr = {
            SIZE_OF_CHARS,
            J
        };
        break;
    case 'L':
        charArr = {
            SIZE_OF_CHARS,
            L
        };
        break;
    case 'M':
        charArr = {
            SIZE_OF_CHARS,
           M
        };
        break;
    case 'N':
        charArr = {
            SIZE_OF_CHARS,
            N
        };
        break;
    case 'P':
        charArr = {
            SIZE_OF_CHARS,
            P
        };
        break;
    case 'R':
        charArr = {
            SIZE_OF_CHARS,
            R
        };
        break;
    case 'T':
        charArr = {
            SIZE_OF_CHARS,
            T
        };
        break;
    case 'U':
        charArr = {
            SIZE_OF_CHARS,
            U
        };
        break;
    case 'V':
        charArr = {
            SIZE_OF_CHARS,
            V
        };
        break;
    case 'W':
        charArr = {
            SIZE_OF_CHARS,
            W
        };
        break;
    case 'Y':
        charArr = {
            SIZE_OF_CHARS,
            Y
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

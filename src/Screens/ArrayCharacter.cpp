#include "ArrayCharacters.h"
#include <Arduino.h>

namespace arrayChar {

const int ZERO[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0100010000000000, 0b0111110000000000 };
const int ONE[SIZE_OF_CHARS] = { 0, 0b0111110000000000, 0 };;
const int TWO[SIZE_OF_CHARS] = { 0b0111010000000000, 0b0101010000000000, 0b0101110000000000 };
const int THREE[SIZE_OF_CHARS] = { 0b0101010000000000, 0b0101010000000000, 0b0111110000000000 };
const int FOUR[SIZE_OF_CHARS] = { 0b0001111000000000, 0b0001000000000000, 0b0111110000000000 };
const int FIVE[SIZE_OF_CHARS] = { 0b0101110000000000, 0b0101010000000000, 0b0111010000000000 };
const int SIX[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0101010000000000, 0b0111010000000000 };
const int SEVEN[SIZE_OF_CHARS] = { 0b0000010000000000, 0b0000010000000000, 0b0111110000000000 };
const int EIGHT[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0101010000000000, 0b0111110000000000 };
const int NINE[SIZE_OF_CHARS] = { 0b0101110000000000, 0b0101010000000000, 0b0111110000000000 };

const int A[SIZE_OF_CHARS] = { 0b0111100000000000, 0b0001010000000000, 0b0111100000000000 };
const int D[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0100010000000000, 0b0011100000000000 };
const int E[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0101010000000000, 0b0101010000000000 };
const int F[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0001010000000000, 0b0001010000000000 };
// const int I[SIZE_OF_CHARS] = { 0, 0b0111110000000000, 0 };
// const int O[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0100010000000000, 0b0111110000000000 };

const int M[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0000100000000000, 0b0111110000000000 };
const int N[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0000100000000000, 0b0111110000000000 };

// const int N[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0001000000000000, 0b0111110000000000 };
const int T[SIZE_OF_CHARS] = { 0b0000010000000000, 0b0111110000000000, 0b0000010000000000 };
const int U[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0100000000000000, 0b0111110000000000 };
const int W[SIZE_OF_CHARS] = { 0b0111110000000000, 0b0010000000000000, 0b0111110000000000 };






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
    case 'W':
        charArr = {
            SIZE_OF_CHARS,
            W
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

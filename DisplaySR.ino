const byte DS = 8;
const byte STCP = 9;
const byte SHCP = 10;
// SEGMENT SELECTOR - HIGH IS OFF
const uint16_t ZERO = 0b0000000000010000;
const uint16_t ONE = 0b0100100001110000;
const uint16_t TWO = 0b0001000000100000;
const uint16_t THREE = 0b0000000001100000;
const uint16_t FOUR = 0b0100100001000000;

const uint16_t FIVE = 0b0010000001000000;
const uint16_t SIX = 0b0010000000000000;
const uint16_t SEVEN = 0b0000100001110000;
const uint16_t EIGHT = 0b0000000000000000;
const uint16_t NINE = 0b0000000001000000;
const uint16_t CLOCK_DIVIDER = 0b0001000000000000;

// DIGIT POSITION SELECTOR - LOW IS OFF
const uint16_t D1 = 0b0000001000000000;
const uint16_t D2 = 0b0000000000001000;
const uint16_t D3 = 0b0000000000000100;
const uint16_t D4 = 0b0000000000000010;
const uint16_t L1 = 0b0000010000000000;

const byte toDisplay[4] = {9, 0, 1, 2};

void setup()
{
    pinMode(DS, OUTPUT);
    pinMode(SHCP, OUTPUT);
    pinMode(STCP, OUTPUT);
}

void loop()
{
    for (int i = 0; i < 4; i++)
    {
        drawNumber(getDigit(toDisplay[i]), getDigitPosition(i));
    }
    drawNumber(CLOCK_DIVIDER, L1);
}

void drawNumber(uint16_t number, uint16_t digit)
{
    uint16_t byteValue = number + digit;
    // IMPORTANT: STCP MUST BE LOW TO RECEIVE DATA
    digitalWrite(STCP, LOW);
    uint16_t test = ONE + D1;
    // shiftOut(DS, SHCP, MSBFIRST, D1);
    shiftOut(DS, SHCP, LSBFIRST, byteValue);
    shiftOut(DS, SHCP, LSBFIRST, byteValue >> 8);

    // IMPORTANT: STCP MUST BE HIGH TO SEND DATA
    digitalWrite(STCP, HIGH);
    delay(2.5);
}

/*
 * Gets the byte representation of the digit position
    0-3 - Selects a digit left to right
    4 - Clock divider
 */
uint16_t getDigitPosition(byte digit)
{
    if (digit < 0 || digit > 4)
    {
        return 0;
    }

    switch (digit)
    {
    case 0:
        return D1;
    case 1:
        return D2;
    case 2:
        return D3;
    case 3:
        return D4;
    case 4:
        return L1;
    }
}
/*Gets the byte representation of the number
  0-9 are numbers
  10 - The clock divider
*/
uint16_t getDigit(byte num)
{
    switch (num)
    {
    case 0:
        return ZERO;
    case 1:
        return ONE;
    case 2:
        return TWO;
    case 3:
        return THREE;
    case 4:
        return FOUR;
    case 5:
        return FIVE;
    case 6:
        return SIX;
    case 7:
        return SEVEN;
    case 8:
        return EIGHT;
    case 9:
        return NINE;
    case 10:
        return CLOCK_DIVIDER;
    default:
        return 0;
        ;
    }
}
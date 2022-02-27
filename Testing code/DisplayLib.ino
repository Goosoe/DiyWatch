/*
  This Display is Common Anode.
  Ports used:
  2 - A & L1 segment
  3 - B & L2 segment
  4 - C segment
  5 - D segment
  6 - E segment
  7 - F segment
  8 - G segment
  9 - Digit selector 1
  10 - Digit selector 2
  11 - Digit selector 3
  12 - Digit selector 4
  13 - L selector 4
*/

// TODO: remove this when module is completed
byte toDisplay[5] = {1, 9, 4, 3};

void setup()
{
  // Serial.begin(9600);

  // DIGIT SELECTORS - LOW IS OFF
  for (byte i = 9; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  // SEGMENT SELECTOR - HIGH IS OFF
  for (byte i = 2; i <= 8; i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
}

void loop()
{
  drawArray(toDisplay, true);
}

// Selects the common anode to write a digit 0 - left-most digit, 3 - right-most, 4 Clock Divider
void selectDigit(byte digit)
{
  if (digit < 0 || digit > 4)
  {
    return;
  }
  switch (digit)
  {
  case 0:
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 1:
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 2:
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
    break;
  case 3:
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
    digitalWrite(13, LOW);
    break;
  case 4:
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    break;
  }
}

/*Draws an array of 4 digits in the display
  REQUIRES: The array must be at least of size 4
*/
void drawArray(byte digits[], boolean useClockDivider)
{
  byte loopArray = 4;
  if (useClockDivider)
  {
    loopArray++;
  }

  for (byte i = 0; i < loopArray; i++)
  {
    selectDigit(i);
    // draws the clock divider
    if (i == 4)
    {
      drawDigit(10);
    }
    else
    {
      drawDigit(digits[i]);
    }
    delay(3.5);
  }
}
/*Draws a digit in the current selected display digit.
  0-9 are numbers
  10 - The clock divider
*/
void drawDigit(byte num)
{
  switch (num)
  {
  case 0:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    break;
  case 1:
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);

    break;
  case 2:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    break;
  case 3:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    break;
  case 4:
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    break;
  case 5:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    break;
  case 6:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    break;
  case 7:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    break;
  case 8:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    break;
  case 9:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    break;
  case 10:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    break;
  default:
      // does nothing
      ;
  }
}
/*Sets all the segment anodes to high, turning them OFF*/
/*void clean() {
  for (int i = 2; i <= 8; i++) {
    digitalWrite(i, HIGH);
  }
  }*/

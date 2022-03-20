const uint8_t BUTTON_ONE = 11;
const uint8_t BUTTON_TWO = 12;

enum COMMANDS {};

namespace controls {
void setup() {
    pinMode(BUTTON_ONE, INPUT);
    pinMode(BUTTON_ONE, INPUT);
}

};  // namespace controls

// Serial.print("Button one: ");
// Serial.println(digitalRead(BUTTON_ONE));
// Serial.print("Button two: ");
// Serial.println(digitalRead(BUTTON_TWO));

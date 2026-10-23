const int BUTTON_PIN = 27;              // not GPIO 34-39: they have no pull-ups
const unsigned long DEBOUNCE_MS = 20;

int lastReading = HIGH;
int stableState = HIGH;
unsigned long lastChange = 0;
int presses = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);           // external 10 k pull-up to 3V3 fitted
  // pinMode(BUTTON_PIN, INPUT_PULLUP); // use this instead if you remove the resistor
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastReading) {
    lastChange = millis();
    lastReading = reading;
  }
  if (millis() - lastChange > DEBOUNCE_MS && reading != stableState) {
    stableState = reading;
    if (stableState == LOW) {
      presses++;
      Serial.printf("Presses: %d\n", presses);
    }
  }
}

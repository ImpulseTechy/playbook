const int BUTTON_PIN = 2;
const unsigned long DEBOUNCE_MS = 20;

int lastReading = HIGH;          // pull-up: HIGH means released
int stableState = HIGH;
unsigned long lastChange = 0;
int presses = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT);    // external 10 k pull-up fitted
  // pinMode(BUTTON_PIN, INPUT_PULLUP);  // use this instead if you remove the resistor
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);
  if (reading != lastReading) {          // the pin changed: restart the timer
    lastChange = millis();
    lastReading = reading;
  }
  if (millis() - lastChange > DEBOUNCE_MS && reading != stableState) {
    stableState = reading;               // stable for 20 ms: accept it
    if (stableState == LOW) {            // active-low: LOW means pressed
      presses++;
      Serial.print("Presses: ");
      Serial.println(presses);
    }
  }
}

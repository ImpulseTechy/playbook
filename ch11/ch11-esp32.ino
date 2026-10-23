const int RELAY_PIN = 25;  // drives the transistor
const int SENSE_PIN = 26;  // NO contact; COM is grounded
const unsigned long TIMEOUT_US = 50000;  // give up after 50 ms

void setup() {
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  pinMode(SENSE_PIN, INPUT_PULLUP);  // HIGH = contact open, LOW = closed
}

// Waits until the sense pin reads 'level'; returns the time taken in microseconds,
// or 0 if it timed out. Only the first change is timed; contact bounce comes later.
unsigned long waitFor(int level, unsigned long t0) {
  while (digitalRead(SENSE_PIN) != level) {
    if (micros() - t0 > TIMEOUT_US) return 0;
  }
  return micros() - t0;
}

void loop() {
  unsigned long t0 = micros();
  digitalWrite(RELAY_PIN, HIGH);
  unsigned long tOn = waitFor(LOW, t0);
  Serial.print("Relay ON.  Operate time: ");
  if (tOn) { Serial.print(tOn / 1000.0, 2); Serial.println(" ms"); }
  else Serial.println("no contact change - check the wiring");
  delay(3000);

  t0 = micros();
  digitalWrite(RELAY_PIN, LOW);
  unsigned long tOff = waitFor(HIGH, t0);
  Serial.print("Relay OFF. Release time: ");
  if (tOff) { Serial.print(tOff / 1000.0, 2); Serial.println(" ms"); }
  else Serial.println("no contact change - check the wiring");
  delay(3000);
}

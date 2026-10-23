const int DATA_PIN  = 23;  // SER   (pin 14)
const int CLOCK_PIN = 18;  // SRCLK (pin 11)
const int LATCH_PIN = 5;   // RCLK  (pin 12)
bool hold = false;

void write595(byte value) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, value);  // QH first, QA last
  digitalWrite(LATCH_PIN, HIGH);                   // rising edge: all 8 outputs update together
}

void setup() {
  Serial.begin(115200);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  write595(0);
  unsigned long t0 = micros();
  write595(0b10101010);
  unsigned long dt = micros() - t0;
  Serial.printf("One update took %lu us\n", dt);
}

void loop() {
  if (Serial.available()) {
    long v = Serial.parseInt();
    while (Serial.available()) Serial.read();
    hold = (v >= 0);
    if (hold) {
      write595((byte)constrain(v, 0, 255));
      Serial.printf("Holding %d\n", (int)constrain(v, 0, 255));
    }
  }
  if (hold) return;
  for (int k = 0; k < 8 && !Serial.available(); k++) { write595(1 << k); delay(150); }
  for (int n = 0; n < 256 && !Serial.available(); n++) { write595(n); delay(40); }
}

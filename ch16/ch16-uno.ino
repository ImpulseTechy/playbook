const int DATA_PIN  = 11;  // SER   (pin 14)
const int CLOCK_PIN = 13;  // SRCLK (pin 11)
const int LATCH_PIN = 10;  // RCLK  (pin 12)
bool hold = false;

void write595(byte value) {
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, value);  // QH first, QA last
  digitalWrite(LATCH_PIN, HIGH);                   // rising edge: all 8 outputs update together
}

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  write595(0);
  unsigned long t0 = micros();
  write595(0b10101010);
  unsigned long dt = micros() - t0;
  Serial.print("One update took "); Serial.print(dt); Serial.println(" us");
}

void loop() {
  if (Serial.available()) {
    long v = Serial.parseInt();
    while (Serial.available()) Serial.read();
    hold = (v >= 0);
    if (hold) {
      write595((byte)constrain(v, 0, 255));
      Serial.print("Holding "); Serial.println((byte)constrain(v, 0, 255), BIN);
    }
  }
  if (hold) return;
  for (int k = 0; k < 8 && !Serial.available(); k++) { write595(1 << k); delay(150); }
  for (int n = 0; n < 256 && !Serial.available(); n++) { write595(n); delay(40); }
}

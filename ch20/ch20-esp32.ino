const int OUT_PIN = 27;    // 555 pin 3, through 10 kOhm with a 1N5819 clamp to 3V3

void setup() {
  Serial.begin(115200);
  pinMode(OUT_PIN, INPUT);
}

void loop() {
  unsigned long th = pulseIn(OUT_PIN, HIGH, 3000000UL);   // up to 3 s
  unsigned long tl = pulseIn(OUT_PIN, LOW, 3000000UL);
  if (th == 0 || tl == 0) { Serial.println("No signal: check the wiring"); return; }
  float f = 1e6 / (th + tl);
  Serial.printf("tH = %.1f ms, tL = %.1f ms, f = %.2f Hz, duty = %.1f %%\n",
                th / 1000.0, tl / 1000.0, f, 100.0 * th / (th + tl));
}

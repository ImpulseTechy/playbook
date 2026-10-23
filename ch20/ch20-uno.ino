const int OUT_PIN = 2;     // 555 pin 3
const int CAP_PIN = A0;    // 555 pins 2 and 6 (the capacitor)
const float VS = 5.0;      // measure your 5V pin and put the real value here
const bool PLOT = false;   // true: capacitor and output in the Serial Plotter

void setup() {
  Serial.begin(9600);
  pinMode(OUT_PIN, INPUT);
}

void loop() {
  if (PLOT) {
    Serial.print("cap:"); Serial.print(analogRead(CAP_PIN) * VS / 1024.0, 2);
    Serial.print(" out:"); Serial.println(digitalRead(OUT_PIN) ? 3.5 : 0.0);
    delay(5);
    return;
  }
  unsigned long th = pulseIn(OUT_PIN, HIGH, 3000000UL);   // up to 3 s
  unsigned long tl = pulseIn(OUT_PIN, LOW, 3000000UL);
  if (th == 0 || tl == 0) { Serial.println("No signal: check the wiring"); return; }
  float f = 1e6 / (th + tl);
  float vmin = 99, vmax = 0;
  unsigned long t0 = micros();
  while (micros() - t0 < 2 * (th + tl)) {                  // two full cycles
    float v = analogRead(CAP_PIN) * VS / 1024.0;
    vmin = min(vmin, v); vmax = max(vmax, v);
  }
  Serial.print("tH = "); Serial.print(th / 1000.0, 1);
  Serial.print(" ms, tL = "); Serial.print(tl / 1000.0, 1);
  Serial.print(" ms, f = "); Serial.print(f, 2);
  Serial.print(" Hz, duty = "); Serial.print(100.0 * th / (th + tl), 1);
  Serial.print(" %, capacitor "); Serial.print(vmin, 2);
  Serial.print("-"); Serial.print(vmax, 2); Serial.println(" V");
}

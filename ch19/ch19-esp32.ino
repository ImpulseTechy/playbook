const int DRIVE_PIN = 25;
const int ADC_PIN = 34;
const float F_LIST[] = {2, 10, 50, 200};
const bool PLOT = false;     // true: 2 Hz square wave and TP3 in the Serial Plotter

float readV() { return analogReadMilliVolts(ADC_PIN) / 1000.0; }

void setup() {
  Serial.begin(115200);
  pinMode(DRIVE_PIN, OUTPUT);
  digitalWrite(DRIVE_PIN, LOW);
  delay(200);
}

void loop() {
  if (PLOT) {
    digitalWrite(DRIVE_PIN, (millis() / 250) % 2);
    Serial.printf("TP3:%.3f\n", readV());
    delay(5);
    return;
  }
  digitalWrite(DRIVE_PIN, LOW); delay(200);
  float bias = 0; for (int n = 0; n < 32; n++) bias += readV(); bias /= 32;
  Serial.printf("Bias: %.3f V\n", bias);

  digitalWrite(DRIVE_PIN, HIGH);                       // a DC input
  float v0 = readV(); delay(15); float v15 = readV(); delay(185); float v200 = readV();
  Serial.printf("Input held HIGH: TP3 = %.2f V at once, %.2f V after 15 ms, %.2f V after 200 ms\n", v0, v15, v200);
  digitalWrite(DRIVE_PIN, LOW); delay(200);

  for (float f : F_LIST) {
    unsigned long half = 500000UL / f;
    float sumA = 0, sumB = 0; int n = 0;
    int cycles = max(6, (int)(f * 0.5));
    for (int c = 0; c < cycles; c++) {
      unsigned long t0 = micros();
      digitalWrite(DRIVE_PIN, HIGH);
      float a = readV();                               // just after the rising edge
      while (micros() - t0 < half - 300) {}
      float b = readV();                               // just before the falling edge
      while (micros() - t0 < half) {}
      digitalWrite(DRIVE_PIN, LOW);
      while (micros() - t0 < 2 * half) {}
      if (c >= 3) { sumA += a - bias; sumB += b - bias; n++; }
    }
    float A = sumA / n, B = sumB / n;
    Serial.printf("%.0f Hz: after edge +%.2f V, before next edge +%.2f V, k = %.3f\n", f, A, B, B / A);
  }
  Serial.println();
  delay(3000);
}

const int DRIVE_PIN = 8;
const int ADC_PIN = A0;
// measure your 5V pin and put the real value here
const float VS = 5.0;
const float F_LIST[] = {2, 10, 50, 200};
// true: 2 Hz square wave and TP3 in the Serial Plotter
const bool PLOT = false;

float readV() { return analogRead(ADC_PIN) * VS / 1024.0; }

void setup() {
  Serial.begin(9600);
  pinMode(DRIVE_PIN, OUTPUT);
  digitalWrite(DRIVE_PIN, LOW);
  delay(200);
}

void loop() {
  if (PLOT) {
    digitalWrite(DRIVE_PIN, (millis() / 250) % 2);
    Serial.print("TP3:"); Serial.println(readV(), 3);
    delay(5);
    return;
  }
  digitalWrite(DRIVE_PIN, LOW); delay(200);
  float bias = 0; for (int n = 0; n < 32; n++) bias += readV(); bias /= 32;
  Serial.print("Bias: "); Serial.print(bias, 3); Serial.println(" V");

  digitalWrite(DRIVE_PIN, HIGH);                       // a DC input
  float v0 = readV();
  delay(15);
  float v15 = readV();
  delay(185);
  float v200 = readV();
  Serial.print("Input held HIGH: TP3 = ");
  Serial.print(v0, 2);
  Serial.print(" V at once, ");
  Serial.print(v15, 2);
  Serial.print(" V after 15 ms, ");
  Serial.print(v200, 2);
  Serial.println(" V after 200 ms");
  digitalWrite(DRIVE_PIN, LOW); delay(200);

  for (float f : F_LIST) {
    unsigned long half = 500000UL / f;
    float sumA = 0, sumB = 0; int n = 0;
    int cycles = max(6, (int)(f * 0.5));
    for (int c = 0; c < cycles; c++) {
      unsigned long t0 = micros();
      digitalWrite(DRIVE_PIN, HIGH);
      // just after the rising edge
      float a = readV();
      while (micros() - t0 < half - 300) {}
      // just before the falling edge
      float b = readV();
      while (micros() - t0 < half) {}
      digitalWrite(DRIVE_PIN, LOW);
      while (micros() - t0 < 2 * half) {}
      if (c >= 3) { sumA += a - bias; sumB += b - bias; n++; }
    }
    float A = sumA / n, B = sumB / n;
    Serial.print(f, 0); Serial.print(" Hz: after edge +"); Serial.print(A, 2);
    Serial.print(" V, before next edge +"); Serial.print(B, 2);
    Serial.print(" V, k = "); Serial.println(B / A, 3);
  }
  Serial.println();
  delay(3000);
}

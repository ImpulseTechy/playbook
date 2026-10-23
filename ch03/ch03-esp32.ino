const float VS = 3.3;    // measure TP1 with your meter and put the real value here
const float R1 = 1000.0, R2 = 2200.0, R3 = 4700.0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  float va = analogReadMilliVolts(34) / 1000.0;   // node A (TP2), about 1.98 V
  float i1 = (VS - va) / R1 * 1000.0;             // mA
  float i2 = va / R2 * 1000.0;                    // mA
  float i3 = va / R3 * 1000.0;                    // mA
  Serial.printf("VA = %.2f V   I1 = %.2f mA   I2 + I3 = %.2f mA\n", va, i1, i2 + i3);
  delay(1000);
}

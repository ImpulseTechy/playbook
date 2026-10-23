const float VS = 5.0;    // measure TP1 with your meter and put the real value here
const float R1 = 1000.0, R2 = 2200.0, R3 = 4700.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float va = analogRead(A0) * VS / 1024.0;   // node A (TP2)
  float i1 = (VS - va) / R1 * 1000.0;        // mA, from R1's voltage
  float i2 = va / R2 * 1000.0;               // mA
  float i3 = va / R3 * 1000.0;               // mA
  Serial.print("VA = ");       Serial.print(va, 2);
  Serial.print(" V   I1 = ");  Serial.print(i1, 2);
  Serial.print(" mA   I2 + I3 = "); Serial.print(i2 + i3, 2);
  Serial.println(" mA");
  delay(1000);
}

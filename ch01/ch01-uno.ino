const int   PIN   = A0;
// measure your UNO's 5V pin and put the real value here
const float VREF  = 5.0;
const float RATIO = (47.0 + 10.0) / 10.0;   // (R1 + R2) / R2 = 5.7

void setup() {
  Serial.begin(9600);
}

void loop() {
  int   raw  = analogRead(PIN);             // 0 to 1023
  float vpin = raw * VREF / 1024.0;         // pin voltage
  float vin  = vpin * RATIO;                // back to battery volts
  Serial.print("Pin: ");      Serial.print(vpin, 3);
  Serial.print(" V   Battery: "); Serial.print(vin, 2);
  Serial.println(" V");
  delay(500);
}

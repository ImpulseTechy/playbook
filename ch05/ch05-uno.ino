// measure the AREF pin with your meter and put the real value here
const float VREF = 1.1;
const float R_SHUNT = 10.0;  // ohm

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL); // 1.1 V reference: about 1.07 mV per step
  // discard readings while the reference settles
  for (int n = 0; n < 5; n++) analogRead(A0);
}

void loop() {
  long sum = 0;
  for (int n = 0; n < 16; n++) sum += analogRead(A0);   // average 16 readings
  float vShunt = (sum / 16.0) * VREF / 1024.0;          // volts
  float current = vShunt / R_SHUNT * 1000.0;            // mA
  Serial.print("Shunt: ");    Serial.print(vShunt * 1000.0, 1);
  Serial.print(" mV   Current: "); Serial.print(current, 2);
  Serial.println(" mA");
  delay(500);
}

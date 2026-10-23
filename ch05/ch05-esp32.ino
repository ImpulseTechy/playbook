const int   PIN = 34;
const float R_SHUNT = 10.0;  // ohm

void setup() {
  Serial.begin(115200);
  // 0 dB: accurate from about 100 to 950 mV
  analogSetPinAttenuation(PIN, ADC_0db);
}

void loop() {
  long sum = 0;
  // average 16 readings
  for (int n = 0; n < 16; n++) sum += analogReadMilliVolts(PIN);
  float mvShunt = sum / 16.0;
  float current = mvShunt / R_SHUNT;      // mV / ohm = mA
  Serial.printf("Shunt: %.1f mV   Current: %.2f mA\n", mvShunt, current);
  delay(500);
}

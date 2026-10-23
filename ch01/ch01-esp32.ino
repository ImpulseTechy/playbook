const int   PIN   = 34;                     // ADC1 pin, works with Wi-Fi on
const float RATIO = (47.0 + 10.0) / 10.0;   // (R1 + R2) / R2 = 5.7

void setup() {
  Serial.begin(115200);
}

void loop() {
  int   mv  = analogReadMilliVolts(PIN);    // calibrated pin voltage in mV
  float vin = mv * RATIO / 1000.0;          // back to battery volts
  Serial.printf("Pin: %4d mV   Battery: %5.2f V\n", mv, vin);
  delay(500);
}

const int ADC_PIN = 34;
// true: print only the voltage, for the Serial Plotter
const bool PLOT = false;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);      // 0-4095 (the default)
}

void loop() {
  long sumRaw = 0, sumMv = 0;
  for (int n = 0; n < 16; n++) {
    sumRaw += analogRead(ADC_PIN);
    sumMv  += analogReadMilliVolts(ADC_PIN);   // factory-calibrated
  }
  float raw = sumRaw / 16.0;
  float v = sumMv / 16.0 / 1000.0;
  if (PLOT) Serial.printf("V:%.3f\n", v);
  else Serial.printf("raw %6.1f   pin %.3f V   (raw x 3.3/4096 = %.3f V)\n",
                     raw, v, raw * 3.3 / 4096.0);
  delay(500);
}

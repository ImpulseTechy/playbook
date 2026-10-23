const int OUT_PIN = 25;
const int ADC_PIN = 34;
const float C_TANK = 100e-9;     // the tank capacitor fitted (F)
// true: print only the detector voltage, for the Serial Plotter
const bool PLOT = false;

float readDet() {
  long sum = 0;
  for (int n = 0; n < 16; n++) sum += analogReadMilliVolts(ADC_PIN);
  return sum / 16.0 / 1000.0;
}

void sweep() {
  float best = 0, fBest = 0;
  for (float f = 800; f <= 16000; f *= 1.04) {
    ledcWriteTone(OUT_PIN, (uint32_t)f);     // 50 % square wave at f
    delay(40);
    float v = readDet();
    if (PLOT) Serial.printf("det:%.3f\n", v);
    else Serial.printf("%.0f Hz: %.3f V\n", f, v);
    if (v > best) { best = v; fBest = f; }
  }
  ledcWriteTone(OUT_PIN, 0);                  // stop
  float Lcalc = 1.0 / (pow(2 * PI * fBest, 2) * C_TANK);
  Serial.printf("Peak at about %.0f Hz (%.3f V): L = %.2f mH\n",
                fBest, best, Lcalc * 1000);
}

void setup() {
  Serial.begin(115200);
  // 0 dB: about 0.1-0.95 V, best for small signals
  analogSetPinAttenuation(ADC_PIN, ADC_0db);
  ledcAttach(OUT_PIN, 1000, 8);               // ESP32 Arduino core 3.x
  sweep();
}

void loop() {
  if (Serial.available()) {
    while (Serial.available()) Serial.read();
    sweep();
  }
}

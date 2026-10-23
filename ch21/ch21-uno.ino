const int OUT_PIN = 8;
const int ADC_PIN = A0;
// measure your 5V pin and put the real value here
const float VS = 5.0;
const float C_TANK = 100e-9;     // the tank capacitor fitted (F)
// true: print only the detector voltage, for the Serial Plotter
const bool PLOT = false;

float readDet() {
  long sum = 0;
  for (int n = 0; n < 16; n++) sum += analogRead(ADC_PIN);
  return sum / 16.0 * VS / 1024.0;
}

void sweep() {
  float best = 0, fBest = 0;
  for (float f = 800; f <= 16000; f *= 1.04) {
    tone(OUT_PIN, (unsigned int)f);
    // let the detector settle (4 x 10 ms)
    delay(40);
    float v = readDet();
    if (PLOT) { Serial.print("det:"); Serial.println(v, 3); }
    else {
      Serial.print(f, 0); Serial.print(" Hz: ");
      Serial.print(v, 3); Serial.println(" V");
    }
    if (v > best) { best = v; fBest = f; }
  }
  noTone(OUT_PIN);
  float Lcalc = 1.0 / (sq(2 * PI * fBest) * C_TANK);
  Serial.print("Peak at about ");
  Serial.print(fBest, 0);
  Serial.print(" Hz (");
  Serial.print(best, 3);
  Serial.print(" V): L = ");
  Serial.print(Lcalc * 1000, 2);
  Serial.println(" mH");
}

void setup() {
  Serial.begin(9600);
  sweep();
}

void loop() {
  if (Serial.available()) {
    while (Serial.available()) Serial.read();
    sweep();
  }
}

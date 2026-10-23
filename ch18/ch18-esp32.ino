const int OUT_PIN = 25;      // filter input
const int ADC_PIN = 34;      // filter output
const int PWM_FREQ = 1000;   // Hz
const float F_LIST[] = {2, 5, 10, 16, 20, 50, 100, 200};

float readV() { return analogReadMilliVolts(ADC_PIN) / 1000.0; }

// Part B: software square wave at f Hz; returns the output's peak-to-peak (V)
float squarePP(float f) {
  unsigned long half = 500000UL / f, t0 = micros(), next = t0 + half;
  unsigned long settle = 100000UL, run = max(settle + 6 * 2 * half, 600000UL);
  bool level = HIGH; digitalWrite(OUT_PIN, level);
  float vmin = 99, vmax = -99;
  while (micros() - t0 < run) {
    if ((long)(micros() - next) >= 0) {
      level = !level;
      digitalWrite(OUT_PIN, level);
      next += half;
    }
    float v = readV();
    if (micros() - t0 > settle) { vmin = min(vmin, v); vmax = max(vmax, v); }
  }
  digitalWrite(OUT_PIN, LOW);
  return vmax - vmin;
}

// Part A: PWM at a duty; prints the output's average and ripple
void pwmTest(int duty) {
  ledcAttach(OUT_PIN, PWM_FREQ, 8);              // ESP32 Arduino core 3.x
  ledcWrite(OUT_PIN, duty * 255 / 100);
  delay(1000);
  float vmin = 99, vmax = -99, sum = 0; int n = 0;
  unsigned long t0 = millis();
  while (millis() - t0 < 500) {
    float v = readV();
    vmin = min(vmin, v);
    vmax = max(vmax, v);
    sum += v;
    n++;
  }
  Serial.printf("PWM %d %%: average %.3f V, ripple %.0f mV p-p\n",
                duty, sum / n, (vmax - vmin) * 1000);
  ledcDetach(OUT_PIN);                           // back to a plain GPIO
  pinMode(OUT_PIN, OUTPUT); digitalWrite(OUT_PIN, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(OUT_PIN, OUTPUT);
}

void loop() {
  Serial.println("Part B: square wave through the filter");
  for (float f : F_LIST) Serial.printf("%.0f Hz: %.2f V p-p\n",
       f, squarePP(f));
  Serial.println("Part A: PWM through the filter");
  pwmTest(25); pwmTest(50); pwmTest(75);
  Serial.println("Send any character to repeat.");
  while (!Serial.available()) {}
  while (Serial.available()) Serial.read();
}

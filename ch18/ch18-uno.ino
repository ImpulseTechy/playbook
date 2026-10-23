const int OUT_PIN = 9;       // filter input (PWM pin)
const int ADC_PIN = A0;      // filter output
const float VS = 5.0;        // measure your 5V pin and put the real value here
const float F_LIST[] = {2, 5, 10, 16, 20, 50, 100, 200};

float readV() { return analogRead(ADC_PIN) * VS / 1024.0; }

// Part B: software square wave at f Hz; returns the output's peak-to-peak (V)
float squarePP(float f) {
  unsigned long half = 500000UL / f, t0 = micros(), next = t0 + half;
  unsigned long settle = 100000UL, run = max(settle + 6 * 2 * half, 600000UL);
  bool level = HIGH; digitalWrite(OUT_PIN, level);
  float vmin = 99, vmax = -99;
  while (micros() - t0 < run) {
    if ((long)(micros() - next) >= 0) { level = !level; digitalWrite(OUT_PIN, level); next += half; }
    float v = readV();
    if (micros() - t0 > settle) { vmin = min(vmin, v); vmax = max(vmax, v); }
  }
  digitalWrite(OUT_PIN, LOW);
  return vmax - vmin;
}

// Part A: PWM at a duty; prints the output's average and ripple
void pwmTest(int duty) {
  analogWrite(OUT_PIN, duty * 255 / 100);
  delay(1000);                                   // settle: more than 5 tau for 10 uF
  float vmin = 99, vmax = -99, sum = 0; int n = 0;
  unsigned long t0 = millis();
  while (millis() - t0 < 500) { float v = readV(); vmin = min(vmin, v); vmax = max(vmax, v); sum += v; n++; }
  Serial.print("PWM "); Serial.print(duty); Serial.print(" %: average ");
  Serial.print(sum / n, 3); Serial.print(" V, ripple ");
  Serial.print((vmax - vmin) * 1000, 0); Serial.println(" mV p-p");
  analogWrite(OUT_PIN, 0);
}

void setup() {
  Serial.begin(9600);
  pinMode(OUT_PIN, OUTPUT);
}

void loop() {
  Serial.println("Part B: square wave through the filter");
  for (float f : F_LIST) {
    float pp = squarePP(f);
    Serial.print(f, 0); Serial.print(" Hz: "); Serial.print(pp, 2); Serial.println(" V p-p");
  }
  Serial.println("Part A: PWM through the filter");
  pwmTest(25); pwmTest(50); pwmTest(75);
  Serial.println("Send any character to repeat.");
  while (!Serial.available()) {}
  while (Serial.available()) Serial.read();
}

const int DRIVE_PIN = 8;
const int SENSE_PIN = A0;
// measure your 5V pin and put the real value here
const float VS = 5.0;
const unsigned long HALF_MS = 5000;  // 5 tau with 10 kOhm and 100 uF
// true: print only the voltage, for the Serial Plotter
const bool PLOT = false;

float readCap() { return analogRead(SENSE_PIN) * VS / 1024.0; }

void runPhase(int level, float target, const char* name) {
  digitalWrite(DRIVE_PIN, level);
  unsigned long t0 = millis(), lastPrint = 0, tau = 0;
  while (millis() - t0 < HALF_MS) {
    float v = readCap();
    unsigned long t = millis() - t0;
    bool crossed = (level == HIGH) ? (v >= target) : (v <= target);
    if (!tau && crossed) tau = t;
    if (t - lastPrint >= 50) {
      lastPrint = t;
      if (PLOT) { Serial.print("V:"); Serial.println(v, 3); }
    }
  }
  if (!PLOT) {
    Serial.print(name); Serial.print(": tau = ");
    Serial.print(tau); Serial.println(" ms");
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(DRIVE_PIN, OUTPUT);
  digitalWrite(DRIVE_PIN, LOW);
  delay(HALF_MS);                  // start fully discharged
}

void loop() {
  runPhase(HIGH, 0.632 * VS, "Charge   ");
  runPhase(LOW,  0.368 * VS, "Discharge");
}

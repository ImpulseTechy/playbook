const int SUPPLY_PIN = 8;          // our switchable "supply"
const int RAIL_PIN = A0;           // watches TP2
const int N = 60;                  // 60 samples, 0.5 ms apart = 30 ms window
int samples[N];

void setup() {
  Serial.begin(115200);
  digitalWrite(SUPPLY_PIN, HIGH);
  pinMode(SUPPLY_PIN, OUTPUT);     // supply on
}

void loop() {
  delay(1000);                     // supply on: the capacitor charges fully
  unsigned long t0 = micros();
  for (int n = 0; n < N; n++) {
    // wait for the next 0.5 ms slot
    while (micros() - t0 < n * 500UL) { }
    if (n == 10) pinMode(SUPPLY_PIN, INPUT);   // 5 ms: supply drops out
    if (n == 30) {                             // 15 ms: supply returns
      digitalWrite(SUPPLY_PIN, HIGH);
      pinMode(SUPPLY_PIN, OUTPUT);
    }
    samples[n] = analogRead(RAIL_PIN);
  }
  for (int n = 0; n < N; n++) {
    Serial.print("rail:");
    Serial.println(samples[n] * 5.0 / 1024.0, 2);
  }
}

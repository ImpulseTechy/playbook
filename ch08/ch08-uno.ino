// (100k + 10k) / 10k; adjust after checking with your meter
const float RATIO = 11.0;
const int N = 120;            // 120 samples x 0.5 ms = 60 ms
int samples[N];

void setup() {
  Serial.begin(115200);
}

void loop() {
  unsigned long t0 = micros();
  for (int n = 0; n < N; n++) {
    while (micros() - t0 < n * 500UL) { }   // one sample every 0.5 ms
    samples[n] = analogRead(A0);
  }
  for (int n = 0; n < N; n++) {
    Serial.print("TP2:");
    Serial.println(samples[n] * 5.0 / 1024.0 * RATIO, 2);
  }
  delay(2000);
}

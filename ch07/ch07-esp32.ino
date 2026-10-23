void setup() {
  Serial.begin(115200);
}

void loop() {
  long sum = 0;
  for (int n = 0; n < 32; n++) sum += analogReadMilliVolts(34);
  float va = sum / 32.0 / 1000.0;
  Serial.printf("Point A: %.3f V\n", va);
  delay(500);
}

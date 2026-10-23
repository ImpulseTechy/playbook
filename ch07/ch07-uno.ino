const float VS = 5.0;    // measure TP1 and put the real value here

void setup() {
  Serial.begin(9600);
}

void loop() {
  long sum = 0;
  for (int n = 0; n < 32; n++) sum += analogRead(A0);
  float va = (sum / 32.0) * VS / 1024.0;
  Serial.print("Point A: ");
  Serial.print(va, 3);
  Serial.println(" V");
  delay(500);
}

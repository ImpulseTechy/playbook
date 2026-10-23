const int LED_PIN = 8;

void setup() {
  pinMode(LED_PIN, OUTPUT);     // without this line the LED glows only faintly
  digitalWrite(LED_PIN, HIGH);  // LED on, steady, for measuring
}

void loop() {
}

const int LED_PIN = 8;

void setup() {
  // without this line the LED glows only faintly
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);  // LED on, steady, for measuring
}

void loop() {
}

int last = HIGH;
void loop() {                      // same code on the UNO and the ESP32
  int r = digitalRead(BUTTON_PIN);
  if (last == HIGH && r == LOW) {  // every HIGH-to-LOW change counts
    presses++;
    Serial.println(presses);
  }
  last = r;
}

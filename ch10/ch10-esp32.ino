const int SWITCH_PIN = 25;

void setup() {
  Serial.begin(115200);
  pinMode(SWITCH_PIN, OUTPUT);
}

void loop() {
  digitalWrite(SWITCH_PIN, HIGH);   // gate at about 3.3 V: on for this small load
  Serial.println("Load ON");
  delay(3000);
  digitalWrite(SWITCH_PIN, LOW);
  Serial.println("Load OFF");
  delay(3000);
}

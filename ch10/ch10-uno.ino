const int SWITCH_PIN = 8;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_PIN, OUTPUT);
}

void loop() {
  digitalWrite(SWITCH_PIN, HIGH);   // gate at about 5 V: fully on
  Serial.println("Load ON");
  delay(3000);
  digitalWrite(SWITCH_PIN, LOW);    // gate at 0 V: off
  Serial.println("Load OFF");
  delay(3000);
}

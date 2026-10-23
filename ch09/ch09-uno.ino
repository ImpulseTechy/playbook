const int SWITCH_PIN = 8;

void setup() {
  Serial.begin(9600);
  pinMode(SWITCH_PIN, OUTPUT);
}

void loop() {
  digitalWrite(SWITCH_PIN, HIGH);
  Serial.println("Load ON");
  delay(3000);
  digitalWrite(SWITCH_PIN, LOW);
  Serial.println("Load OFF");
  delay(3000);
}

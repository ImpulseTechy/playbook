const int IN_PIN = 2;    // the protected node, through column 8
int last = -1;

void setup() {
  Serial.begin(9600);
  pinMode(IN_PIN, INPUT);   // the 100 kOhm pull-down holds it LOW
}

void loop() {
  int now = digitalRead(IN_PIN);
  if (now != last) {
    Serial.println(now == HIGH ? "Signal HIGH" : "Signal LOW");
    last = now;
  }
  delay(20);
}

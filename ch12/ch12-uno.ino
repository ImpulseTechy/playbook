const int EN  = 9;   // EN1: HIGH = outputs on, LOW = coast
const int IN1 = 8;   // 1A
const int IN2 = 7;   // 2A

void setup() {
  Serial.begin(9600);
  pinMode(EN, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(EN, LOW);   // start with the motor off
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(EN, HIGH);
}
void reverse() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(EN, HIGH);
}
void brake() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(EN, HIGH);
}
void coast()   { digitalWrite(EN, LOW); }

void loop() {
  forward(); Serial.println("Forward"); delay(3000);
  coast();   Serial.println("Coast");   delay(2000);
  reverse(); Serial.println("Reverse"); delay(3000);
  brake();   Serial.println("Brake");   delay(2000);
}

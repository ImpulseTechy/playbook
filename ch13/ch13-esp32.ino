const int PWM_PIN = 25;  // Part A: LED resistor. Part B: L293D EN1.
const int IN1 = 26;      // Part B: L293D 1A
const int IN2 = 27;      // Part B: L293D 2A
const int FREQ = 1000;   // PWM frequency (Hz). Keep at or below 5000 for the L293D.
const int RES  = 8;      // resolution (bits): duty values 0-255

void setup() {
  Serial.begin(115200);
  ledcAttach(PWM_PIN, FREQ, RES);   // ESP32 Arduino core 3.x
  ledcWrite(PWM_PIN, 0);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  digitalWrite(IN1, HIGH);   // Part B: forward
  digitalWrite(IN2, LOW);
  Serial.println("Type a duty cycle from 0 to 100 (%) and press Enter.");
}

void loop() {
  if (Serial.available()) {
    long pct = Serial.parseInt();
    while (Serial.available()) Serial.read();   // discard the newline
    pct = constrain(pct, 0, 100);
    int value = (pct * 255 + 50) / 100;          // 0-100 % -> 0-255, rounded
    ledcWrite(PWM_PIN, value);
    Serial.print("Duty "); Serial.print(pct);
    Serial.print(" % (value "); Serial.print(value);
    Serial.println(" of 255)");
  }
}

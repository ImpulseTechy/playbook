const int IN_PIN  = 2;    // Part A: PC817 collector, 10 kOhm pull-up to 5 V
const int OUT_PIN = 9;    // Part B: PC817 LED, through 330 Ohm
const int LED_PIN = 13;   // the UNO's built-in LED shows the input state

bool lastInput = HIGH;
unsigned long lastToggle = 0;
bool outState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(IN_PIN, INPUT);       // the external 10 kOhm pull-up holds it HIGH
  pinMode(OUT_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Ready.");
}

void loop() {
  // Part A: the opto pulls the pin LOW when the isolated input is ON
  bool input = digitalRead(IN_PIN);
  if (input != lastInput) {
    Serial.println(input == LOW ? "Input ON  (pin LOW)" : "Input OFF (pin HIGH)");
    lastInput = input;
  }
  digitalWrite(LED_PIN, input == LOW ? HIGH : LOW);

  // Part B: switch the opto's LED every 3 seconds
  if (millis() - lastToggle >= 3000) {
    lastToggle = millis();
    outState = !outState;
    digitalWrite(OUT_PIN, outState);
    Serial.println(outState ? "Output: opto LED ON" : "Output: opto LED OFF");
  }
}

const int ADC_PIN = A0;
float VS = 5.0;                  // the UNO's 5 V: measure the 5V pin and put the real value here
const float BANDGAP = 1.1;       // internal reference, 1.0-1.2 V: calibrate it in Experiment 6
const bool PLOT = false;         // true: print only the voltage, for the Serial Plotter

float readVcc() {                // measures the 1.1 V reference against the supply
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);                      // let the reference settle
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC)) {}
  return BANDGAP * 1024.0 / ADC; // supply = 1.1 V x 1024 / reading
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  float vcc = readVcc();
  analogRead(ADC_PIN);           // discard one reading after switching channels
  long sum = 0;
  for (int n = 0; n < 16; n++) sum += analogRead(ADC_PIN);
  float raw = sum / 16.0;
  float v = raw * VS / 1024.0;
  if (PLOT) { Serial.print("V:"); Serial.println(v, 3); }
  else {
    Serial.print("raw "); Serial.print(raw, 1);
    Serial.print("   pin "); Serial.print(v, 3);
    Serial.print(" V   supply (internal) "); Serial.print(vcc, 3); Serial.println(" V");
  }
  delay(500);
}

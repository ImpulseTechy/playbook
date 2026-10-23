#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;          // default I2C address 0x40

void setup() {
  Serial.begin(115200);          // UNO users can keep 115200 or change to 9600
  if (!ina219.begin()) {
    Serial.println("INA219 not found: check SDA, SCL, VCC and GND");
    while (true) delay(10);
  }
  ina219.setCalibration_16V_400mA();   // best resolution for small currents
}

void loop() {
  Serial.print("Bus: ");      Serial.print(ina219.getBusVoltage_V(), 2);
  Serial.print(" V   Shunt: ");   Serial.print(ina219.getShuntVoltage_mV(), 2);
  Serial.print(" mV   Current: "); Serial.print(ina219.getCurrent_mA(), 1);
  Serial.print(" mA   Power: ");   Serial.print(ina219.getPower_mW(), 0);
  Serial.println(" mW");
  delay(500);
}

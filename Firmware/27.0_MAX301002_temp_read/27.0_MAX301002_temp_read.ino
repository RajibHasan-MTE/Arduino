#include <Wire.h>

#include "MAX30105.h"
MAX30105 particleSensor;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Initialize sensor
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) { //Use default I2C port, 400kHz speed
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }

  //The LEDs are very low power and won't affect the temp reading much but
  //you may want to turn off the LEDs to avoid any local heating
  particleSensor.setup(0); //Configure sensor. Turn off LEDs

  particleSensor.enableDIETEMPRDY(); //Enable the temp ready interrupt. This is required.
}

void loop() {
  float temperature = particleSensor.readTemperature();

  Serial.print("temperatureC=");
  Serial.print(temperature, 4);

  float temperatureF = particleSensor.readTemperatureF();

  Serial.print(" temperatureF=");
  Serial.print(temperatureF, 4);

  Serial.println();
}
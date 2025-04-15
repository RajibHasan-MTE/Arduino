#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
#define REPORTING_PERIOD_MS     1000
 // MAX30100 I2C address
#define MAX30100_ADDRESS 0x57

PulseOximeter pox;
uint32_t tsLastReport = 0;
 
void onBeatDetected()
{   digitalWrite(LED_BUILTIN, HIGH);
    static bool ledState = 1;
    Serial.println("Beat!");
    
}
 
void setup()
{
    Serial.begin(9600);
    Serial.print("Initializing pulse oximeter..");
    pinMode(LED_BUILTIN, OUTPUT);

 
    // Initialize the PulseOximeter instance
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}
 
void loop()
{
    // Make sure to call update as fast as possible
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");
 
        tsLastReport = millis();
        digitalWrite(LED_BUILTIN, LOW);
    }
}




#include <HardwareSerial.h>

// Define UART1 for GSM (SIM800L)
HardwareSerial sim800l(1);
// Define UART2 for GPS (NEO-6M)
HardwareSerial gps(2);

void setup() {
  Serial.begin(9600);       // Debugging (UART0)
  sim800l.begin(9600, SERIAL_8N1, 16, 17); // TX=17, RX=16
  gps.begin(9600, SERIAL_8N1, 4, 3);       // TX=4, RX=3
}

void loop() {
  // Read GPS data
  if (gps.available()) {
    String gpsData = gps.readString();
    Serial.println("GPS: " + gpsData);
  }

  // Read SIM800L response
  if (sim800l.available()) {
    String gsmData = sim800l.readString();
    Serial.println("GSM: " + gsmData);
  }
}

#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Initialize GPS Serial connection
HardwareSerial SerialGPS(2); // Using UART2 (e.g., GPIO16, GPIO17)

// Create an instance of TinyGPS++
TinyGPSPlus gps;

void setup() {
  // Initialize Serial for Debugging
  Serial.begin(9600);
  Serial.println("GPS Module Test");

  // Initialize GPS Serial (Change GPIO pins as per your connections)
   SerialGPS.begin(9600, SERIAL_8N1, 16, 17); // RX=GPIO16, TX=GPIO17
  //SerialGPS.begin(9600, SERIAL_8N1, 34, 35); // RX=GPIO16, TX=GPIO17

}

void loop() {
  // Continuously read data from GPS module
  while (SerialGPS.available() > 0) {
    char c = SerialGPS.read(); // Read each character
    if (gps.encode(c)) {       // If the character is valid, process it
      displayGPSInfo();
    }
  }

  // Display a message if no GPS data is available
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS data received: Check connections.");
  }
}

// Function to display GPS information
void displayGPSInfo() {
  // Check if location data is valid
  if (gps.location.isValid()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6); // 6 decimal places for precision

    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);

    Serial.print("Altitude: ");
    Serial.print(gps.altitude.meters());
    Serial.println(" meters");

    Serial.print("Speed: ");
    Serial.print(gps.speed.kmph());
    Serial.println(" km/h");

    Serial.print("Satellites: ");
    Serial.println(gps.satellites.value());

    Serial.print("Date: ");
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());

    Serial.print("Time: ");
    Serial.print(gps.time.hour());
    Serial.print(":");
    Serial.print(gps.time.minute());
    Serial.print(":");
    Serial.println(gps.time.second());
  } else {
    Serial.println("Location data is invalid.");
  }

  Serial.println("---------------------------------");
  delay(1000); // Wait for a second before updating
}

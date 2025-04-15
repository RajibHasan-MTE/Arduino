#include <SoftwareSerial.h>

#define PWRKEY_PIN 9 // Connect PWRKEY pin of SIM7000G to Arduino pin 9

SoftwareSerial gsmSerial(7, 8); // RX, TX pins connected to SIM7000G module

void setup() {
  pinMode(PWRKEY_PIN, OUTPUT); // Set PWRKEY pin as output
  digitalWrite(PWRKEY_PIN, HIGH); // Keep PWRKEY high initially

  gsmSerial.begin(9600); // Set GSM module communication baud rate
  Serial.begin(9600);    // For debugging via serial monitor

  Serial.println("Powering on the GSM module...");
  powerOnGSM();

  Serial.println("Initializing GSM module...");
  delay(2000); // Wait for the module to stabilize

  // Send AT command to check communication
  gsmSerial.println("AT");
  delay(1000);
  if (gsmSerial.available()) {
    Serial.println("GSM Module Ready!");
    while (gsmSerial.available()) {
      Serial.write(gsmSerial.read());
    }
  } else {
    Serial.println("GSM Module not responding. Check connections.");
    while (true); // Stop execution if module not detected
  }

  // Make a call
  makeCall("+8801869675414");
}

void loop() {
  // Nothing to do in the loop
}

void makeCall(const char *phoneNumber) {
  // Send ATD command to dial the number
  String command = "ATD";
  command += phoneNumber;
  command += ";"; // End of AT command for dialing
  gsmSerial.println(command);

  Serial.println("Dialing number...");
  delay(10000); // Wait for the call to go through

  // Hang up the call
  //hangUp();
}

void hangUp() {
  gsmSerial.println("ATH"); // Send ATH to hang up
  Serial.println("Call ended.");
}

void powerOnGSM() {
  // Pull PWRKEY low for 2 seconds to turn on the module
  digitalWrite(PWRKEY_PIN, LOW);
  delay(2000);
  digitalWrite(PWRKEY_PIN, HIGH); // Release the pin
  delay(3000); // Wait for the module to power up
}

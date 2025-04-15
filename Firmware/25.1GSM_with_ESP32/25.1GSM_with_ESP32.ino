void setup() {
  Serial.begin(115200);   // Debug Serial Monitor
  Serial2.begin(9600, SERIAL_8N1, 16, 17);  // GPS UART2 on GPIO16 (RX2) and GPIO17 (TX2)
  delay(3000);

  Serial.println("Initializing SIM800L...");
  test_sim800_module();
  send_SMS();
}

void loop() {
  if (Serial2.available()) {   // Check for data from SIM800L
    while (Serial2.available()) {
      char c = Serial2.read();
      Serial.write(c);          // Forward GSM data to Serial Monitor
    }
  }
}

void test_sim800_module() {
  Serial.println("Testing SIM800L...");
  sendATCommand("AT");           // Test communication
  sendATCommand("AT+CSQ");       // Signal quality
  sendATCommand("AT+CCID");      // SIM card ID
  sendATCommand("AT+CREG?");     // Network registration
}

void send_SMS() {
  Serial.println("Sending SMS...");
  sendATCommand("AT+CMGF=1");                  // Set SMS to text mode
  sendATCommand("AT+CMGS=\"+880186975414\"");  // Enter recipient phone number
  Serial2.print("Hello from ESP32!");          // Enter SMS content
  delay(100);
  Serial2.write(26);                           // ASCII CTRL+Z to send
  Serial.println("Message Sent!");
}

void sendATCommand(String command) {
  Serial2.println(command);     // Send AT command to SIM800L
  delay(500);                   // Wait for response
  while (Serial2.available()) { // Read and display response
    char c = Serial2.read();
    Serial.write(c);
  }
  Serial.println();
}

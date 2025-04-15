// Define pins for HX710B
const int dataPin = 2; // DOUT
const int clockPin = 3; // SCK

void setup() {
  pinMode(dataPin, INPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
}

long readHX710B() {
  long result = 0;

  // Wait for the module to be ready
  while (digitalRead(dataPin) == HIGH);

  // Read 24-bit data
  for (int i = 0; i < 24; i++) {
    digitalWrite(clockPin, HIGH);
    result = (result << 1) | digitalRead(dataPin);
    digitalWrite(clockPin, LOW);
  }

  // Apply clock pulse to complete the conversion
  digitalWrite(clockPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(clockPin, LOW);

  // Return the 24-bit result
  return result;
}

void loop() {
  long pressureValue = readHX710B();

  Serial.print("Pressure (raw value): ");
  Serial.println(pressureValue);

  // Add a delay
  delay(500);
}
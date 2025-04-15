#include <DHT.h>

// Define the pin where the DHT11 sensor is connected
#define DHTPIN 32  

// Define the sensor type (DHT11)
#define DHTTYPE DHT11   

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println("DHT11 Sensor Reading...");
    dht.begin();
}

void loop() {
    // Wait a bit between sensor readings
    delay(2000);

    // Read temperature and humidity
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Check if the reading is valid
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Display data
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
}

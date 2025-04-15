uuu#include <Wire.h>

const int MPU6050_ADDR = 0x68; // MPU6050 I2C address

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Wake up MPU6050 (default is in sleep mode)
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B); // Power Management 1 register
    Wire.write(0);    // Wake up MPU6050
    Wire.endTransmission();
    Serial.println("Hello");
    delay(2000);
}

void loop() {
    int16_t accelX, accelY, accelZ, gyroX, gyroY, gyroZ;

    // Request accelerometer and gyroscope data
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B); // Starting register for accelerometer data
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 14, true);

    // Read accelerometer data
    accelX = (Wire.read() << 8) | Wire.read();
    accelY = (Wire.read() << 8) | Wire.read();
    accelZ = (Wire.read() << 8) | Wire.read();

    Wire.read(); // Temperature data (not used)
    Wire.read();

    // Read gyroscope data
    gyroX = (Wire.read() << 8) | Wire.read();
    gyroY = (Wire.read() << 8) | Wire.read();
    gyroZ = (Wire.read() << 8) | Wire.read();

    // Display values on Serial Monitor
    Serial.print("Accel: ");
    Serial.print(accelX); Serial.print(", ");
    Serial.print(accelY); Serial.print(", ");
    Serial.print(accelZ); Serial.print(" | ");

    Serial.print("Gyro: ");
    Serial.print(gyroX); Serial.print(", ");
    Serial.print(gyroY); Serial.print(", ");
    Serial.println(gyroZ);

    delay(500);
}

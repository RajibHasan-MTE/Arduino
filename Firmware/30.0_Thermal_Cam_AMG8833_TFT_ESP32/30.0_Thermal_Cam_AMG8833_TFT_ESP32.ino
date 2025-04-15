#include <Wire.h>
#include <Adafruit_AMG88xx.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// // TFT Display Pins
// #define TFT_CS    13
// #define TFT_DC    12
// #define TFT_RST   0

//ESP32-WROOM
#define TFT_DC 12 //A0
#define TFT_CS 13 //CS
#define TFT_MOSI 14 //SDA
#define TFT_CLK 27 //SCK
#define TFT_RST 0  
#define TFT_MISO 0 

// Initialize TFT Display
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);
// Initialize AMG8833 Sensor
Adafruit_AMG88xx amg;

// Sensor Resolution
#define AMG88xx_PIXEL_ARRAY_SIZE 8
float pixels[AMG88xx_PIXEL_ARRAY_SIZE * AMG88xx_PIXEL_ARRAY_SIZE];

// Display Resolution
// #define TFT_WIDTH  128
// #define TFT_HEIGHT 160

#define TFT_WIDTH  160
#define TFT_HEIGHT 128

// Color Mapping
uint16_t getColor(float val) {
  val = constrain(val, 20, 35); // Constrain temperature range for better visualization
  uint8_t r, g, b;

  // Map temperature to RGB values
  if (val < 23) {
    r = 0;
    g = map(val, 20, 23, 0, 255);
    b = 255;
  } else if (val < 26) {
    r = 0;
    g = 255;
    b = map(val, 23, 26, 255, 0);
  } else if (val < 29) {
    r = map(val, 26, 29, 0, 255);
    g = 255;
    b = 0;
  } else {
    r = 255;
    g = map(val, 29, 35, 255, 0);
    b = 0;
  }

  return tft.color565(r, g, b);
}

void setup() {
  Serial.begin(115200);

  // Initialize TFT Display
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(1); // Adjust rotation if needed

  // Initialize AMG8833 Sensor
  if (!amg.begin()) {
    Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
    while (1);
  }
  Serial.println("AMG88xx sensor initialized!");

  delay(100); // Let sensor stabilize
}

void loop() {
  // Read temperature data from AMG8833
  amg.readPixels(pixels);

  // Display thermal image on TFT
  for (int y = 0; y < AMG88xx_PIXEL_ARRAY_SIZE; y++) {
    for (int x = 0; x < AMG88xx_PIXEL_ARRAY_SIZE; x++) {
      float temp = pixels[y * AMG88xx_PIXEL_ARRAY_SIZE + x];
      uint16_t color = getColor(temp);

      // Scale the 8x8 grid to 128x160 display
      int x0 = x * (TFT_WIDTH / AMG88xx_PIXEL_ARRAY_SIZE);
      int y0 = y * (TFT_HEIGHT / AMG88xx_PIXEL_ARRAY_SIZE);
      int x1 = x0 + (TFT_WIDTH / AMG88xx_PIXEL_ARRAY_SIZE) - 1;
      int y1 = y0 + (TFT_HEIGHT / AMG88xx_PIXEL_ARRAY_SIZE) - 1;

      tft.fillRect(x0, y0, x1 - x0 + 1, y1 - y0 + 1, color);
    }
  }

  delay(5); // Adjust delay for refresh rate
}
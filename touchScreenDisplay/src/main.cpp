#include <SPI.h>
#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup(void) {
  tft.begin();
  tft.setTextSize(2);
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
}

void loop() {
  tft.println("Line 1");
  tft.println("Line 2");
  tft.println("Line 3");
  delay(1000);
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
}









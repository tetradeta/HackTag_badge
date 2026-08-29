#include "Arduino.h"

#include "SPI.h"
#include <TFT_eSPI.h>


TFT_eSPI tft=TFT_eSPI();

void setup() {

  pinMode(5, OUTPUT);
  pinMode(17, OUTPUT);

  digitalWrite(5, HIGH);
  digitalWrite(17, HIGH);

  Serial.begin(115200);

  tft.init();

  tft.fillScreen(TFT_RED);

  Serial.println("Lowkey дисплей виноват");

}

void loop() {

}
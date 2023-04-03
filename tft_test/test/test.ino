#include <TFT_eSPI.h>
#include "trex.h"

#define left 43
#define right 44

TFT_eSPI tft = TFT_eSPI();

void setup() {
  pinMode(15, OUTPUT);  // to be able to boot with battery
  digitalWrite(15, 1);  // and/or power from 5v rail instead of USB port

  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(40, 10, 90, 90, trex);
}

bool state = false;
bool lastState = false;
void loop() {
  state = !digitalRead(right);
  if (state != lastState) {
    if (state){
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(80, 10, 90, 90, trex);
    }
    else{
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(40, 10, 90, 90, trex);
    }
    
  }
  lastState = state;
}
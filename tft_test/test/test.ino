#include <TFT_eSPI.h>
#include "AssetsManager.h"

#define LEFT_PIN 43
#define RIGHT_PIN 44
#define BUZZER_PIN 18

TFT_eSPI tft = TFT_eSPI();
AssetsManager* assets = AssetsManager::getInstance();

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(15, OUTPUT);  // to be able to boot with battery
  digitalWrite(15, 1);  // and/or power from 5v rail instead of USB port

  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.pushImage(40, 10, 90, 90, assets->getAsset(DINO)->getBMP());
}

bool state = false;
bool lastState = false;

void loop() {
  tone(BUZZER_PIN, 500, 100);
  state = !digitalRead(RIGHT_PIN);
  if (state != lastState) {
    if (state) {
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(80, 10, 90, 90, assets->getAsset(DINO)->getBMP());
      tft.pushImage(0, 0, 320, 170, assets->getAsset(BACKGROUND)->getBMP());
      tft.pushImage(0, 0, 320, 170, assets->getAsset(MENU)->getBMP());
      tft.pushImage(0, 0, 320, 170, assets->getAsset(BIRD)->getBMP());
    } else {
      tft.fillScreen(TFT_BLACK);
      tft.pushImage(40, 10, 90, 90, assets->getAsset(DINO)->getBMP());
    }
  }
  lastState = state;
}
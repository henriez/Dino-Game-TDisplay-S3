#pragma once
#include "Asset.h"
//#include <Arduino.h> // esp32

#define DINO 1
#define CROUCH 2
#define CACTUS1 3
#define CACTUS2 4
#define CACTUS3 5
#define CACTUS4 6
#define BIRD 7
#define MENU 8
#define BACKGROUND 9
#define GAMEOVER 10

using namespace std;


class AssetsManager {
public:

  ~AssetsManager();

  static AssetsManager* getInstance();
  static void deleteInstance();

  Asset* getAsset(int assetName);

private:
  AssetsManager();
  static AssetsManager* manager;
  Asset* dino;
  Asset* crouch;
  Asset* bird;
  Asset* cactus1;
  Asset* cactus2;
  Asset* cactus3;
  Asset* cactus4;
  Asset* menu;
  Asset* background;
  Asset* gameover;
};
#pragma once
#include "Asset.h"
#include <Arduino.h> // esp32

#define ASSET_DINO 1
#define ASSET_CROUCH 2
#define ASSET_CACTUS1 3
#define ASSET_CACTUS2 4
#define ASSET_CACTUS3 5
#define ASSET_CACTUS4 6
#define ASSET_BIRD 7
#define ASSET_MENU 8
#define ASSET_BACKGROUND 9
#define ASSET_GAMEOVER 10


class AssetsManager {
public:
  // Destructor
  ~AssetsManager();

  // Singleton method
  static AssetsManager* getInstance();

  // Singleton method
  static void deleteInstance();

  // Return an asset based on name
  Asset* getAsset(int assetName);

private:
  // Singleton requires private constructor
  AssetsManager();

  // Singleton static pointer
  static AssetsManager* manager;

  // Assets
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
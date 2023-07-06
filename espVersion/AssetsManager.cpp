#include "AssetsManager.h"

#include "trex.h"
#include "crouch.h"
#include "cactus1.h"
#include "cactus2.h"
#include "cactus3.h"
#include "cactus4.h"
#include "birdBMP.h"
#include "menu.h"
#include "backgroundBMP.h"
#include "gameover.h"

// Static pointer initialization
AssetsManager* AssetsManager::manager = NULL;

// Singleton private constructor
AssetsManager::AssetsManager() {
  dino = new Asset(trexBMP, 54, 54);
  crouch = new Asset(crouchBMP, 54, 27);

  bird = new Asset(birdBMP, 42, 32);

  cactus1 = new Asset(cactus1BMP, 11, 24);
  cactus2 = new Asset(cactus2BMP, 18, 36);
  cactus3 = new Asset(cactus3BMP, 50, 36);
  cactus4 = new Asset(cactus4BMP, 35, 36);

  menu = new Asset(menuBMP, 320, 170);
  background = new Asset(backgroundBMP, 640, 30);
  gameover = new Asset(gameoverBMP, 320, 170);

}

// Destructor
AssetsManager::~AssetsManager() {
  delete dino;
  delete crouch;
  delete bird;
  delete cactus1;
  delete cactus2;
  delete cactus3;
  delete cactus4;
  delete menu;
  delete background;
  delete gameover;
}

// Singleton method
AssetsManager* AssetsManager::getInstance() {
  if (!manager)
    manager = new AssetsManager();

  return manager;
}

// Singleton method
void AssetsManager::deleteInstance() {
  if (manager)
    delete manager;
}

// Return an asset based on name
Asset* AssetsManager::getAsset(int assetName) {
  switch(assetName){
    case ASSET_DINO:
      return dino;
    case ASSET_CROUCH:
      return crouch;
    case ASSET_BIRD:
      return bird;
    case ASSET_CACTUS1:
      return cactus1;
    case ASSET_CACTUS2:
      return cactus2;
    case ASSET_CACTUS3:
      return cactus3;
    case ASSET_CACTUS4:
      return cactus4;
    case ASSET_MENU:
      return menu;
    case ASSET_BACKGROUND:
      return background;
    case ASSET_GAMEOVER:
      return gameover;
    default:
      return nullptr;
  }
  
}
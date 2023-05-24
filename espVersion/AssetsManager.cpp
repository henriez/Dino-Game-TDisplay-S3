#include "AssetsManager.h"

// esp32 only
#include "trex.h"
#include "crouch.h"
#include "cactus1.h"
#include "cactus2.h"
#include "cactus3.h"
#include "cactus4.h"
#include "birdBMP.h"
#include "menu.h"
#include "background.h"
#include "gameover.h"

AssetsManager* AssetsManager::manager = NULL;

AssetsManager::AssetsManager() {
  // ESP32
  dino = new Asset(trexBMP, 54, 54);
  crouch = new Asset(crouchBMP, 54, 27);

  bird = new Asset(birdBMP, 42, 32);

  cactus1 = new Asset(cactus1BMP, 11, 24);
  cactus2 = new Asset(cactus2BMP, 18, 36);
  cactus3 = new Asset(cactus3BMP, 50, 36);
  cactus4 = new Asset(cactus4BMP, 35, 36);

  menu = new Asset(menuBMP, 320, 170);
  background = new Asset(backgroundBMP, 320, 170);
  gameover = new Asset(gameoverBMP, 320, 170);

}

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

AssetsManager* AssetsManager::getInstance() {
  if (!manager)
    manager = new AssetsManager();

  return manager;
}

void AssetsManager::deleteInstance() {
  if (manager)
    delete manager;
}

Asset* AssetsManager::getAsset(int assetName) {
  switch(assetName){
    case DINO:
      return dino;
    case CROUCH:
      return crouch;
    case BIRD:
      return bird;
    case CACTUS1:
      return cactus1;
    case CACTUS2:
      return cactus2;
    case CACTUS3:
      return cactus3;
    case CACTUS4:
      return cactus4;
    case MENU:
      return menu;
    case BACKGROUND:
      return background;
    case GAMEOVER:
      return gameover;
    default:
      return nullptr;
  }
  
}
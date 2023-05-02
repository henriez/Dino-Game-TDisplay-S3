#include "AssetsManager.h"
#include <iostream>
using namespace std;


AssetsManager* AssetsManager::manager = NULL;

AssetsManager::AssetsManager() {
  // ESP32
  // dino = new Asset(dinoBMP, 54, 54);
  // crouch = new Asset(crouchBMP, 54, 27);

  // bird = new Asset(birdBMP, 42, 32);

  // cactus1 = new Asset(cactus1BMP, 11, 24);
  // cactus2 = new Asset(cactus2BMP, 18, 36);
  // cactus3 = new Asset(cactus3BMP, 50, 36);
  // cactus4 = new Asset(cactus4BMP, 35, 36);

  // menu = new Asset(menuBMP, 320, 170);
  // background = new Asset(backgroundBMP, 320, 170);

  // PC
  dino = new Asset("assets/trex.bmp", 54, 54);
  crouch = new Asset("assets/crouch.bmp", 54, 27);

  bird = new Asset("assets/bird.bmp", 42, 32);

  cactus1 = new Asset("assets/cactus1.bmp", 11, 24);
  cactus2 = new Asset("assets/cactus2.bmp", 18, 36);
  cactus3 = new Asset("assets/cactus3.bmp", 50, 36);
  cactus4 = new Asset("assets/cactus4.bmp", 35, 36);

  menu = new Asset("assets/menu.bmp", 320, 170);
  background = new Asset("assets/background.bmp", 320, 170);

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
    default:
      return nullptr;
  }
  
}
#include "GraphicsManager.h"
#include <iostream>
using namespace std;

GraphicsManager *GraphicsManager::manager = NULL;

GraphicsManager::GraphicsManager() {
  tft.init();
  assets = AssetsManager::getInstance();
}

GraphicsManager::~GraphicsManager() {
  AssetsManager::deleteInstance();
}

GraphicsManager *GraphicsManager::getInstance() {
  if (!manager)
    manager = new GraphicsManager();

  return manager;
}

void GraphicsManager::deleteInstance() {
  if (manager)
    delete manager;
}


void GraphicsManager::clear() {
  tft.fillScreen(TFT_BLACK);
}

// ESP32 version
void GraphicsManager::render(int x, int y, string assetName) {
  Asset *img = assets->getAsset(assetName);
  tft.pushImage(x, y, img->getW(), img->getH(), img->getBMP());
}

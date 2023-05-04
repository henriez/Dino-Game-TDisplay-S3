#include "GraphicsManager.h"
GraphicsManager *GraphicsManager::manager = NULL;

GraphicsManager::GraphicsManager() {
  tft->init();  // esp32 version
  tft->setRotation(1);
  sprite = new TFT_eSprite(tft);
  sprite->createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);

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
  sprite->fillScreen(TFT_BLACK);  // ESP32 version
}

void GraphicsManager::present() {
  sprite->pushSprite(0, 0, TFT_BLACK);
}


// ESP32 version
void GraphicsManager::render(int x, int y, int assetName, int srcX, int srcY) {
  Asset *img = assets->getAsset(assetName);
  sprite->pushImage(x, y, img->getW(), img->getH(), img->getBMP());
}

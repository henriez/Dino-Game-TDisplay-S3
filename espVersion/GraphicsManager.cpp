#include "GraphicsManager.h"
GraphicsManager *GraphicsManager::manager = NULL;

TFT_eSPI tft;  // esp32
TFT_eSprite sprite = TFT_eSprite(&tft);

GraphicsManager::GraphicsManager() {
  tft.init();  // esp32 version
  tft.fillScreen(TFT_BLACK);
  sprite.createSprite(SCREEN_HEIGHT, SCREEN_WIDTH);

  assets = AssetsManager::getInstance();
}

GraphicsManager::~GraphicsManager() {
  AssetsManager::deleteInstance();
  sprite.deleteSprite();
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
  sprite.fillSprite(TFT_BLACK);  // ESP32 version
}

void GraphicsManager::present() {
  sprite.pushSprite(0, 0);
}


// ESP32 version
void GraphicsManager::render(int x, int y, int assetName, int srcX, int srcY) {
  Asset *img = assets->getAsset(assetName);
  sprite.pushImage(y, x, img->getH(), img->getW(), img->getBMP());
}

#include "GraphicsManager.h"

// Static private pointer initialization
GraphicsManager *GraphicsManager::manager = NULL;

// TFT_eSPI renderer
TFT_eSPI tft;

/** TFT_eSprite
  * All assets are pushed to the sprite and then the sprite is 
  * pushed to the renderer, to avoid flickering
  */
TFT_eSprite sprite = TFT_eSprite(&tft);

// Singleton Private constructor
GraphicsManager::GraphicsManager() {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);

  // Rotates all coordinates system
  tft.setSwapBytes(true);
  tft.setRotation(1);

  sprite.createSprite(320, 170);
  sprite.setSwapBytes(true);
  sprite.setTextSize(2);

  assets = AssetsManager::getInstance();
}

// Destructor
GraphicsManager::~GraphicsManager() {
  AssetsManager::deleteInstance();
  sprite.deleteSprite();
}

// Singlethon method
GraphicsManager *GraphicsManager::getInstance() {
  if (!manager)
    manager = new GraphicsManager();

  return manager;
}

// Singleton method
void GraphicsManager::deleteInstance() {
  if (manager)
    delete manager;
}

// Clear sprite for next rendering proccess
void GraphicsManager::clear() {
  sprite.fillSprite(TFT_BLACK);
}

// Push sprite to screen
void GraphicsManager::present() {
  sprite.pushSprite(0, 0);
}

// Render asset at (x,y)
void GraphicsManager::render(int x, int y, int assetName) {
  Asset *img = assets->getAsset(assetName);
  sprite.pushImage(x, y, img->getW(), img->getH(), img->getBMP());
}

// Render text at (x,y)
void GraphicsManager::renderText(int x, int y, String str) {
  sprite.drawString(str, x, y);
}

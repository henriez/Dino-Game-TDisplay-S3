#include "GraphicsManager.h"
#include <iostream>
using namespace std;

GraphicsManager *GraphicsManager::manager = NULL;

GraphicsManager::GraphicsManager()
{
  // tft.init(); // esp32 version

  assets = AssetsManager::getInstance();

  // ================ PC ONLY =============================== //
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow("DINO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (!window)
  {
    cout << "Error: Failed to open window\nSDL Error:" << SDL_GetError();
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  Asset *tmp = assets->getAsset(DINO);
  addTexture(tmp->getPath(), DINO);
  tmp = assets->getAsset(CROUCH);
  addTexture(tmp->getPath(), CROUCH);

  tmp = assets->getAsset(BIRD);
  addTexture(tmp->getPath(), BIRD);

  tmp = assets->getAsset(CACTUS1);
  addTexture(tmp->getPath(), CACTUS1);
  tmp = assets->getAsset(CACTUS2);
  addTexture(tmp->getPath(), CACTUS2);
  tmp = assets->getAsset(CACTUS3);
  addTexture(tmp->getPath(), CACTUS3);
  tmp = assets->getAsset(CACTUS4);
  addTexture(tmp->getPath(), CACTUS4);

  tmp = assets->getAsset(MENU);
  addTexture(tmp->getPath(), MENU);
  tmp = assets->getAsset(BACKGROUND);
  addTexture(tmp->getPath(), BACKGROUND);
  tmp = assets->getAsset(GAMEOVER);
  addTexture(tmp->getPath(), GAMEOVER);

  // ================ PC ONLY =============================== //
  
}

GraphicsManager::~GraphicsManager()
{
  // ================ PC ONLY =============================== //
  map<int, SDL_Texture *>::iterator i = textures.begin();
  for (i = textures.begin(); i != textures.end(); i++)
  {
    SDL_DestroyTexture(i->second);
  }

  textures.clear();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  // ================ PC ONLY =============================== //

  AssetsManager::deleteInstance();
}

GraphicsManager *GraphicsManager::getInstance()
{
  if (!manager)
    manager = new GraphicsManager();

  return manager;
}

void GraphicsManager::deleteInstance()
{
  if (manager)
    delete manager;
}

void GraphicsManager::clear()
{
  SDL_RenderClear(renderer); // pc version
  // tft.fillScreen(TFT_BLACK); // ESP32 version
}

// PC only
void GraphicsManager::addTexture(string path, int assetName)
{
  SDL_Surface *tmpSurface = SDL_LoadBMP(path.c_str());

  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);

  if (tex)
    textures.insert(std::make_pair(assetName, tex));

  else
  {
    cout << "failed creating texture " << SDL_GetError() << endl;
    SDL_FreeSurface(tmpSurface);
    return;
  }
  SDL_FreeSurface(tmpSurface);
}

// PC only
void GraphicsManager::present()
{
  SDL_RenderPresent(renderer);
}

// ESP32 version
// void GraphicsManager::render(int x, int y, int assetName)
// {
//   Asset *img = assets->getAsset(assetName);
//   tft.pushImage(x, y, img->getW(), img->getH(), img->getBMP());
// }

void GraphicsManager::render(int x, int y, int assetName, int srcX, int srcY)
{
  Asset *img = assets->getAsset(assetName);
  SDL_Texture *tex;

  tex = textures[assetName];
  if (!tex)
  {
    string path = img->getPath();
    addTexture(path, assetName);
    tex = textures[assetName];
  }
  SDL_Rect src = {srcX, srcY, img->getW(), img->getH()};
  SDL_Rect dest = {x, y, img->getW(), img->getH()};
  SDL_RenderCopy(renderer, tex, &src, &dest);
}

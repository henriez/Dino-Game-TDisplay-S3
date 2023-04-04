#include "headers/GraphicsManager.h"
#include <iostream>
using namespace std;

GraphicsManager *GraphicsManager::manager = NULL;

GraphicsManager::GraphicsManager()
{
    assets = AssetsManager::getInstance();
    window = SDL_CreateWindow("DINO", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        cout << "Error: Failed to open window\nSDL Error:" << SDL_GetError();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    Asset *dino = assets->getAsset("dino");
    addTexture(dino->getPath(), "dino");
}

GraphicsManager::~GraphicsManager()
{

    map<string, SDL_Texture *>::iterator i = textures.begin();
    for (i = textures.begin(); i != textures.end(); i++)
    {
        SDL_DestroyTexture(i->second);
    }

    textures.clear();
    AssetsManager::deleteInstance();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
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

// PC only
void GraphicsManager::addTexture(string path, string assetName)
{
    SDL_Surface *tmpSurface = SDL_LoadBMP(path.c_str());

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    if (tex)
        textures.insert(std::make_pair(assetName, tex));
    
    else{
        cout << "failed creating texture " << SDL_GetError() << endl;
        SDL_FreeSurface(tmpSurface);
        return;
    }
    SDL_FreeSurface(tmpSurface);
}

// PC version
void GraphicsManager::clear()
{
    SDL_RenderClear(renderer);
}

// PC version
void GraphicsManager::render(int x, int y, string assetName)
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
    SDL_Rect src = {0, 0, img->getW(), img->getH()};
    SDL_Rect dest = {x, y, img->getW(), img->getH()};
    SDL_RenderCopy(renderer, tex, &src, &dest);
}

// PC only
void GraphicsManager::present()
{
    SDL_RenderPresent(renderer);
}

/*
// ESP32 version
void GraphicsManager::clear(){
    tft.fillScreen(TFT_BLACK);
}

// ESP32 version
void GraphicsManager::render(int x, int y, string assetName){
    Asset* img = assets->getAsset(assetName);
    tft.pushImage(x, y, img->getW(), img->getH(), img->getBMP());
}
*/
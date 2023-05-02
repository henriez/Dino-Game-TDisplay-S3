#pragma once
#include <map> // pc
#include <SDL2/SDL.h>
#include "AssetsManager.h"

using namespace std;

#define SCREEN_WIDTH 320 
#define SCREEN_HEIGHT 170


class GraphicsManager
{
public:
    ~GraphicsManager();

    static GraphicsManager* getInstance();
	static void deleteInstance();

    void addTexture(string path, int assetName); // pc

    //void render(int x, int y, int assetName); // esp32
    void render(int x, int y, int assetName, int srcX=0, int srcY=0); // pc
    void present(); // PC only
    void clear();

private:
    GraphicsManager();
    static GraphicsManager* manager;
    AssetsManager* assets;

    //TFT_eSPI tft0; //esp32 version
    SDL_Renderer* renderer; // PC version
    SDL_Window* window; // PC version
    map<int, SDL_Texture*> textures; // PC only
};
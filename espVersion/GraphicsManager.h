#pragma once
#include <map> // pc
//#include <SDL2/SDL.h> // pc
#include <TFT_eSPI.h> //esp32 
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

    //void addTexture(string path, int assetName); // pc only

    void render(int x, int y, int assetName, int srcX=0, int srcY=0);
    //void present(); // PC only
    void clear();

private:
    GraphicsManager();
    static GraphicsManager* manager;
    AssetsManager* assets;

    TFT_eSPI tft; // esp32
    //SDL_Renderer* renderer; // PC only
    //SDL_Window* window; // PC only
    //map<int, SDL_Texture*> textures; // PC only
};
#pragma once
#include <map>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

#define SCREEN_WIDTH 320 
#define SCREEN_HEIGHT 170


class GraphicsManager
{
public:
    ~GraphicsManager();

    static GraphicsManager* getInstance();
	static void deleteInstance();

    void render(int x, int y, string assetName);
    void clear();
    void addTexture(string path, string assetName);

private:
    GraphicsManager();
    static GraphicsManager* manager;

    //TFT_eSPI tft; // ESP32 version
    SDL_Renderer* renderer; // PC version
    SDL_Window* window; // PC version
    map<string, SDL_Texture*> textures;
};
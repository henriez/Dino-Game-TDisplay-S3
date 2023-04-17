#pragma once
#include <map>
#include <string>
//#include <TFT_eSPI.h>
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

    void render(int x, int y, string assetName);
    void present(); // PC only
    void clear();

private:
    GraphicsManager();
    static GraphicsManager* manager;
    AssetsManager* assets;

    TFT_eSPI tft; // ESP32 version
};
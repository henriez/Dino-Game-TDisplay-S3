#pragma once
#include <TFT_eSPI.h>
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
    void renderBackground(int dx);
    void present(); // PC only
    void clear();

private:
    GraphicsManager();
    static GraphicsManager* manager;
    AssetsManager* assets;

};
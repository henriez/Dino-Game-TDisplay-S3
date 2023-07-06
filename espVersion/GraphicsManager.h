#pragma once
#include <TFT_eSPI.h>
#include "AssetsManager.h"

using namespace std;

// Macros for screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 170

class GraphicsManager {
public:
  // Destructor
  ~GraphicsManager();

  // Singleton method
  static GraphicsManager* getInstance();

  // Singleton method
  static void deleteInstance();

  // Render asset at (x,y)
  void render(int x, int y, int assetName);

  // Render text at (x,y)
  void renderText(int x, int y, String str);

  // Push sprite to screen
  void present();

  // Clear sprite for next rendering proccess
  void clear();

private:
  // Singleton requires private constructor
  GraphicsManager();

  // Singleton static pointer
  static GraphicsManager* manager;

  // Assets manager intermediates images PROGMEM pointers
  AssetsManager* assets;

};
#pragma once

#include "GraphicsManager.h"

class Game
{
public:
    ~Game();

    static Game *getInstance();
    static void deleteInstance();

    void run();

private:
    Game();
    static Game *game;
    bool running;
    SDL_Event event;
    GraphicsManager* graphics;
    string state;
};
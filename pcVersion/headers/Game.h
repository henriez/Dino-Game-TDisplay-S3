#pragma once

#include "GraphicsManager.h"
#include "CollisionManager.h"
#include "Dino.h"
#include "Cactus.h"
#include "Bird.h"

class Game
{
public:
    ~Game();

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void handleEvents();
    void handleEventsMenu();

private:
    Game();
    static Game *game;
    bool running;
    SDL_Event event;
    GraphicsManager* graphics;
    CollisionManager* collision;
    Bird* bird;
    Dino* dino;

    int state;
};
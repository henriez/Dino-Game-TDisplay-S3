#pragma once

#include "GraphicsManager.h"
#include "CollisionManager.h"
#include "Dino.h"
#include "Cactus.h"
#include "Bird.h"

#define LEFT_PIN 0 // esp32
#define RIGHT_PIN 14 // esp32

class Game
{
public:
    ~Game();

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void handleEvents();
    void handleEventsMenu();

    void scrollBackground();
    unsigned long calculateDeltaTime();

private:
    Game();
    static Game *game;
    bool running;
    GraphicsManager* graphics;
    CollisionManager* collision;
    Cactus* cactus;
    Bird* bird;
    Dino* dino;
    unsigned long start, end, gameStart;

    int state;
};
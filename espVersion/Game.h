#pragma once

#include <Arduino.h>
#include "GraphicsManager.h"
#include "CollisionManager.h"
#include "Dino.h"
#include "Cactus.h"
#include "Bird.h"

#define LEFT_PIN 0
#define RIGHT_PIN 14

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
    float calculateDeltaTime();

private:
    Game();
    static Game *game;
    bool running;
    GraphicsManager* graphics;
    CollisionManager* collision;
    Cactus* cactus;
    Bird* bird;
    Dino* dino;
    float startFrame, start, end;

    int state;
};
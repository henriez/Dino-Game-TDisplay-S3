#pragma once

#include "GraphicsManager.h"
#include "CollisionManager.h"
#include "Dino.h"
#include "Cactus.h"
#include "Bird.h"

#define LEFT_PIN 43 // esp32
#define RIGHT_PIN 16 // esp32
// #define LEFT_PIN 0 // esp32
// #define RIGHT_PIN 14 // esp32
#define BUZZER_PIN 18  

class Game
{
public:
    ~Game();

    static Game *getInstance();
    static void deleteInstance();

    void run();
    void handleEvents();
    void handleEventsMenu();
    void reset();
    void renew(int entity);

    int scrollBackground();
    unsigned long deltaTime();

private:
    Game();
    static Game *game;
    GraphicsManager* graphics;
    CollisionManager* collision;
    Cactus* cactus;
    Bird* bird;
    Dino* dino;
    unsigned long start, end, gameStart;

    int state, right_prev_state, left_prev_state;
};
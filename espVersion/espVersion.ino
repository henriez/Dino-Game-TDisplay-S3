#include <iostream>
#include "Game.h"

Game* game;
void setup() {
    game = Game::getInstance();

}

void loop() {
    game->run();

    Game::deleteInstance();
}

Game::deleteInstance();
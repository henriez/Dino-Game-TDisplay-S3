#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]){

    Game* game = Game::getInstance();

    game->run();

    Game::deleteInstance();

    return 0;
}
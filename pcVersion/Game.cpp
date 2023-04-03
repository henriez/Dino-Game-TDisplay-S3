#include "headers/Game.h"

Game *Game::game = nullptr;

Game::Game() : running(true) {
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = GraphicsManager::getInstance();
}

Game::~Game() {}

Game *Game::getInstance()
{
    if (!game)
        game = new Game();

    return game;
}

void Game::deleteInstance()
{
    if (game)
        delete game;
}

void Game::run()
{
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            default:
                break;
            }
        }
    }
}

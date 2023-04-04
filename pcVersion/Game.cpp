#include "headers/Game.h"

Game *Game::game = NULL;

Game::Game() : running(true) {
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = GraphicsManager::getInstance();
}

Game::~Game() {
    GraphicsManager::deleteInstance();
}

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

        graphics->render(40, 40, "dino");
        graphics->present();
    }
}

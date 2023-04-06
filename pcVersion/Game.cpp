#include "headers/Game.h"
#define FRAMETIME 40

Game *Game::game = NULL;

Game::Game() : running(true)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = GraphicsManager::getInstance();
    collision = CollisionManager::getInstance();
    dino = new Dino;
}

Game::~Game()
{
    GraphicsManager::deleteInstance();
    CollisionManager::deleteInstance();
    delete dino;
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
    Uint32 start, end;
    while (running)
    {
        graphics->clear();
        start = SDL_GetTicks();
        handleEvents();

        dino->update();
        graphics->present();

        end = SDL_GetTicks();
        if ((end - start) < FRAMETIME)
            SDL_Delay(FRAMETIME - (end - start));
    }
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        cout << event.type << endl;
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        case 768:
            if (event.key.keysym.sym == SDLK_s)
                dino->crouch();

            break;

        case 769:
            if (event.key.keysym.sym == SDLK_w)
                dino->jump();

            break;

        default:
            break;
        }
    }
}

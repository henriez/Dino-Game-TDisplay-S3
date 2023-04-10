#include "headers/Game.h"
#define FRAMETIME 40
#define STATE_MENU 1
#define STATE_RUNNING 2

Game *Game::game = NULL;

Game::Game() : running(true)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    graphics = GraphicsManager::getInstance();
    collision = CollisionManager::getInstance();
    dino = new Dino;
    state = STATE_MENU;
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

        if (state == STATE_MENU)
        {
            handleEventsMenu();
            graphics->render(0, 0, "menu");
        }
        else if (state == STATE_RUNNING)
        {
            graphics->render(0, 0, "background");
            handleEvents();
            dino->update();
        }

        end = SDL_GetTicks();
        if ((end - start) < FRAMETIME)
            SDL_Delay(FRAMETIME - (end - start));
        graphics->present();
    }
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
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

void Game::handleEventsMenu()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;

        case 769:
            if (event.key.keysym.sym == SDLK_w)
                state = STATE_RUNNING;

            break;

        default:
            break;
        }
    }
}

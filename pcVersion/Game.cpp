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
    bird = new Bird;
    cactus = new Cactus;
    state = STATE_MENU;
    start = end = 0;
}

Game::~Game()
{
    GraphicsManager::deleteInstance();
    CollisionManager::deleteInstance();
    delete dino;
    delete bird;
    delete cactus;
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
        graphics->clear();
        start = SDL_GetTicks();

        if (state == STATE_MENU)
        {
            handleEventsMenu();
            graphics->render(0, 0, "menu");
        }
        else if (state == STATE_RUNNING)
        {
            scrollBackground();
            handleEvents();
            dino->update();
            bird->update();
            cactus->update();
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
            else if (event.key.keysym.sym == SDLK_s)
                dino->stand();

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

void Game::scrollBackground()
{
    end = SDL_GetTicks();
    Uint32 deltaTime = end - start;
    double k = 0.0000008;
    double x = 0;
    double v0 = 0.06;

    x = v0*end + k*(end*end);    

    int srcX = (int)(x) % 320;
    graphics->render(0, 0, "background", srcX);
    
    cactus->updateCactus(-x);
}
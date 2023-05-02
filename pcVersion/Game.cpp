#include "Game.h"
#define FRAMETIME 40
#define STATE_MENU 1
#define STATE_RUNNING 2
#define STATE_GAMEOVER 3

// pc only
#define LOW 10
#define HIGH 11

// pc only: substitutes arduino.h functions
unsigned long millis()
{
  return SDL_GetTicks();
}

void delay(int ms)
{
  SDL_Delay(ms);
}

Game *Game::game = NULL;

Game::Game()
    : running(true)
{
  graphics = GraphicsManager::getInstance();

  collision = CollisionManager::getInstance();
  dino = new Dino;
  bird = new Bird;
  cactus = new Cactus(CACTUS_MODEL_1);
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
    start = millis();

    if (state == STATE_MENU)
    {
      handleEventsMenu();
      graphics->render(0, 0, MENU);
    }
    else if (state == STATE_RUNNING)
    {
      scrollBackground(); // como fazer essa na esp?
      handleEvents();
      dino->update();
      if (collision->collide(dino, cactus) || collision->collide(dino, bird))
      {
        state = STATE_GAMEOVER;
        reset();
      }
      if (collision->outOfBounds(cactus))
        cactus->renew();
      if (collision->outOfBounds(bird))
        bird->renew();
    }
    else if (state == STATE_GAMEOVER)
    {
      handleEventsMenu();
      graphics->render(0, 0, GAMEOVER);
    }

    end = millis();
    if ((end - start) < FRAMETIME)
      delay(FRAMETIME - (end - start));
    graphics->present(); // pc
  }
}

// esp32
/*
void Game::handleEvents()
{
  if (digitalRead(LEFT_PIN) == LOW) //check if its low or high
    dino->crouch();

  if (digitalRead(RIGHT_PIN) == HIGH) //check if its low or high
    dino->jump();
  // if (event.key.keysym.sym == SDLK_s)
  //  dino->stand();
}*/

void Game::reset()
{
  delete dino;
  dino = new Dino;
  delete bird;
  bird = new Bird;
  delete cactus;
  cactus = new Cactus;
}

// pc
void Game::handleEvents()
{
  SDL_Event event;
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

// esp32
/*
void Game::handleEventsMenu()
{
  bool onMenu = false;
  while (onMenu)
  {
    if (digitalRead(RIGHT_PIN))
    {
      state = STATE_RUNNING;
      onMenu = true;
      start = millis();
      cactus->startTimer(start);
    }
  }
}*/

// pc
void Game::handleEventsMenu()
{
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type)
  {
  case SDL_QUIT:
    running = false;
    break;

  case 769:
    if (event.key.keysym.sym == SDLK_w)
    {
      state = STATE_RUNNING;
      gameStart = SDL_GetTicks();
    }

    break;

  default:
    break;
  }
}

void Game::scrollBackground()
{
  end = millis() - gameStart;
  double x = 0;

  // x = v0t + at²/2
  x = 0.23 * end + 0.0000008 * (end * end);

  int srcX = (int)(x) % 320;
  graphics->render(0, 0, BACKGROUND, srcX);

  cactus->update(-x);
  bird->update(-x);
}

unsigned long Game::calculateDeltaTime()
{
  unsigned long oldTime = end;
  end = millis();
  unsigned long deltaTime = end - oldTime;
  return deltaTime;
}
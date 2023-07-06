#include "Game.h"
#define FRAMETIME 40
#define STATE_MENU 1
#define STATE_RUNNING 2
#define STATE_GAMEOVER 3

#define RENEW_CACTUS 4
#define RENEW_BIRD 5

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
    start = millis();
    graphics->clear();

    if (state == STATE_MENU)
    {
      graphics->render(0, 0, MENU);
      graphics->present();
      handleEventsMenu();
    }
    else if (state == STATE_RUNNING)
    {
      scrollBackground(); // como fazer essa na esp?
      handleEvents();
      dino->update();
      if (collision->collide(dino, cactus) || collision->collide(dino, bird))
        reset();
      if (collision->outOfBounds(cactus))
        renew(RENEW_CACTUS);
      if (collision->outOfBounds(bird))
        renew(RENEW_BIRD);
      graphics->present();
    }
    else if (state == STATE_GAMEOVER)
    {
      graphics->render(0, 0, GAMEOVER);
      graphics->present();
      handleEventsMenu();
    }

    end = millis();

    if ((end - start) < FRAMETIME)
      delay(FRAMETIME - (end - start));
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
  state = STATE_GAMEOVER;
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

void Game::renew(int entity)
{
  unsigned long t = millis() - gameStart;
  int minDX = (0.23 + 0.0000016 * t) * (15 * FRAMETIME); // vx * dt (dt = tempo de ar do dino)

  end = millis() - gameStart;
  int px = SCREEN_WIDTH + rand() % 100; // mudar logica de spawn
  int model;
  // define nova posicao e novo modelo de cacto
  if (entity == RENEW_CACTUS)
  {
    if (px - bird->getCollider().x < minDX)
      px = bird->getCollider().x + minDX; // minimo de distancia entre cada obstaculo
    // cout << "renewing cactus: px = " << px << " | bird.x = " << bird->getCollider().x << endl;
    if (end > 50000)
    {
      model = rand() % 4;
    }
    else
      model = rand() % 2;

    cactus->renew(model, px);
  }
  // define nova posicao de passaro
  else if (entity == RENEW_BIRD)
  {
    if (px - cactus->getCollider().x < minDX) // mudar valor para logica com tempo - alcance horizontal
      px = cactus->getCollider().x + minDX;   // minimo de distancia entre cada obstaculo
    // cout << "renewing bird: px = " << px << " | cactus.x = " << cactus->getCollider().x << endl;
    bird->renew(0, px);
  }
}

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
  unsigned long long t = 0;
  t = millis() - gameStart;
  double x = 0, vx = 0, dx = 0;

  // x = v0t + at²/2
  x = 0.23 * t + 0.0000008 * (t * t);
  // v = dx/dt = v0 + at
  vx = 0.23 + 0.0000016 * t;
  dx = vx * deltaTime();
  int srcX = (int)(x) % 320;
  graphics->render(0, 0, BACKGROUND, srcX);

  cactus->update(-dx);
  bird->update(-dx);
}

unsigned long Game::deltaTime()
{
  return millis() - end;
}

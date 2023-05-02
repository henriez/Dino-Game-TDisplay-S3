#include "Game.h"
#define FRAMETIME 40
#define STATE_MENU 1
#define STATE_RUNNING 2

Game *Game::game = NULL;

Game::Game()
  : running(true) {
  graphics = GraphicsManager::getInstance();
  collision = CollisionManager::getInstance();
  dino = new Dino;
  bird = new Bird;
  cactus = new Cactus(CACTUS_MODEL_2);
  state = STATE_MENU;
  start = endtime = 0;
}

Game::~Game() {
  GraphicsManager::deleteInstance();
  CollisionManager::deleteInstance();
  delete dino;
  delete bird;
  delete cactus;
}

Game *Game::getInstance() {
  if (!game)
    game = new Game();

  return game;
}

void Game::deleteInstance() {
  if (game)
    delete game;
}

void Game::run() {
  while (running) {
    graphics->clear();
    startFrame = millis();

    if (state == STATE_MENU) {
      handleEventsMenu();
      graphics->render(0, 0, MENU);
    } else if (state == STATE_RUNNING) {
      scrollBackground();
      handleEvents();
      dino->update();
      bird->update();
      cactus->update();
    }

    endtime = millis();
    if ((endtime - start) < FRAMETIME)
      delay(FRAMETIME - (endtime - startFrame));
    graphics->present();
  }
}

void Game::handleEvents() {
  if (digitalRead(LEFT_PIN) == LOW)
    dino->crouch();


  if (digitalRead(RIGHT_PIN) == HIGH)
    dino->jump();
  // if (event.key.keysym.sym == SDLK_s)
  //  dino->stand();
}

void Game::handleEventsMenu() {
  bool onMenu = false;
  while (onMenu) {
    if (digitalRead(RIGHT_PIN)){
        state = STATE_RUNNING;
        onMenu = true;
        start = millis();
      }
  }
}

void Game::scrollBackground() {
  endtime = millis() - start;
  double k = 0.0000008;
  double x = 0;
  double v0 = 0.12;

  x = v0 * endtime + k * (endtime * endtime);

  int srcX = (int)(x) % 320;
  graphics->render(0, 0, BACKGROUND);

  cactus->updateCactus(-x);  // PROBLEMA COM INICIALIZACAO, TIMER "END" INICIA CONTAGEM NO MENU (antes de iniciar o jogo)
}

unsigned long Game::calculateDeltaTime() {
  unsigned long oldTime = endtime;
  endtime = millis();
  unsigned long deltaTime = endtime - oldTime;
  return deltaTime;
}
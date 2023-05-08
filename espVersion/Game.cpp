#include "Game.h"
#define FRAMETIME 40
#define STATE_MENU 1
#define STATE_RUNNING 2
#define STATE_GAMEOVER 3

#define RENEW_CACTUS 4
#define RENEW_BIRD 5

// pc only
#define LOW 10
#define HIGH 11

// pc only: substitutes arduino.h functions
// unsigned long millis()
// {
//   return SDL_GetTicks();
// }

// void delay(int ms)
// {
//   SDL_Delay(ms);
// }

Game *Game::game = NULL;

Game::Game() {
  graphics = GraphicsManager::getInstance();
  Serial.begin(9600);

  collision = CollisionManager::getInstance();
  dino = new Dino;
  bird = new Bird;
  cactus = new Cactus;
  state = STATE_MENU;
  start = end = right_prev_state = left_prev_state = 0;
  graphics->clear();
  graphics->render(0, 0, MENU);
  graphics->present();
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

  start = millis();
  graphics->clear();

  if (state == STATE_MENU) {
    graphics->render(0, 0, MENU);
    graphics->present();
    handleEventsMenu();
  } else if (state == STATE_RUNNING) {
    scrollBackground();  // como fazer essa na esp?
    handleEvents();
    dino->update();
    if (collision->collide(dino, cactus) || collision->collide(dino, bird))
      reset();
    if (collision->outOfBounds(cactus))
      renew(RENEW_CACTUS);
    if (collision->outOfBounds(bird))
      renew(RENEW_BIRD);
    graphics->present();
  } else if (state == STATE_GAMEOVER) {
    graphics->render(0, 0, GAMEOVER);
    graphics->present();
    handleEventsMenu();
  }

  end = millis();

  if ((end - start) < FRAMETIME)
    delay(FRAMETIME - (end - start));
}

void Game::handleEvents() {
  if (!digitalRead(LEFT_PIN))
    dino->crouch();

  if (!digitalRead(RIGHT_PIN) && digitalRead(RIGHT_PIN) != right_prev_state)
    dino->jump();
    
  if (digitalRead(LEFT_PIN) && digitalRead(LEFT_PIN) != left_prev_state)
    dino->stand();

  left_prev_state = digitalRead(LEFT_PIN);
  right_prev_state = digitalRead(RIGHT_PIN);
}

void Game::renew(int entity){
  end = millis() - gameStart;
  int px = 0;
  // define nova posicao e novo modelo de cacto
  if (entity == RENEW_CACTUS){
    if (end > 50000){
      model = rand()%4;
      cactus->renew(model, px);
    }
  }
  // define nova posicao de passaro
  else if (entity == RENEW_BIRD){
    bird->renew(0, px);
  }
  lastPosition = px;
}

void Game::reset() {
  // delete dino;
  // dino = new Dino;
  // delete bird;
  // bird = new Bird;
  // delete cactus;
  // cactus = new Cactus;
  // state = STATE_GAMEOVER;

  Serial.println("collided!");
}

// esp32

void Game::handleEventsMenu() {
  bool onMenu = true;
  while (onMenu) {
    if (!digitalRead(RIGHT_PIN) && digitalRead(RIGHT_PIN) != right_prev_state) {
      state = STATE_RUNNING;
      onMenu = false;
      gameStart = millis();
    }
    right_prev_state = digitalRead(RIGHT_PIN);
  }
}

void Game::scrollBackground() {
  end = millis() - gameStart;
  double x = 0;

  // x = v0t + at²/2
  x = 0.12 * end + 0.0000008 * (end * end);

  int srcX = (int)(x) % 320;
  //graphics->render(0, 0, BACKGROUND, srcX); // nao sei se funciona na esp
  //criar sprite background e pushSprite em X negativo

  cactus->update(-x);
  bird->update(-x);
}

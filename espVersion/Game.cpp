#include "Game.h"

#include <SPIFFS.h>
#include <FS.h>

// Macro for limiting max FPS at 25 (1000/40)
#define FRAMETIME 40

// Macros for heandling game state
#define STATE_MENU 1
#define STATE_RUNNING 2
#define STATE_GAMEOVER 3

// Macros for calling renew functions
#define RENEW_CACTUS 4
#define RENEW_BIRD 5

// Static private pointer initialization
Game *Game::game = NULL;

// Private constructor
Game::Game() {

  graphics = GraphicsManager::getInstance();
  collision = CollisionManager::getInstance();

  Serial.begin(9600);

  // Get maxScore saved
  SPIFFS.begin();
  fs::File file = SPIFFS.open("/pontos.txt", "r");
  if (!file)
    Serial.println("Couldn't open score file for reading");
  else
    maxScore = file.readString().toInt();
  file.close();

  // Create entities
  dino = new Dino;
  bird = new Bird;
  cactus = new Cactus;

  state = STATE_MENU;
  start = end = right_prev_state = left_prev_state = score = px = 0;

  firstFrame = true;

  // Starts menu
  graphics->clear();
  graphics->render(0, 0, ASSET_MENU);
  graphics->present();
}

// Destructor
Game::~Game() {
  GraphicsManager::deleteInstance();
  CollisionManager::deleteInstance();
  delete dino;
  delete bird;
  delete cactus;
}

// Singleton method
Game *Game::getInstance() {
  if (!game)
    game = new Game();

  return game;
}

// Singleton method
void Game::deleteInstance() {
  if (game)
    delete game;
}

// Main function inside Game, checks states, calls update, render and renew
void Game::run() {

  start = millis();

  graphics->clear();

  handleEvents();

  if (state == STATE_RUNNING) {
    int dx = scrollBackground();
    px += dx;
    px %= 320;
    graphics->render(-px, 110, ASSET_BACKGROUND);

    dino->update();
    cactus->update(-dx);
    bird->update(-dx);

    dino->render();
    cactus->render();
    bird->render();

    graphics->renderText(10, 10, String(score));
    graphics->renderText(250, 10, "HI:");
    graphics->renderText(290, 10, String(maxScore));

    if (collision->outOfBounds(cactus))
      renew(RENEW_CACTUS);
    if (collision->outOfBounds(bird))
      renew(RENEW_BIRD);
    if (collision->collide(dino, cactus) || collision->collide(dino, bird))
      reset();
  }


  graphics->present();

  // Sets max FPS
  end = millis();
  if ((end - start) < FRAMETIME)
    delay(FRAMETIME - (end - start));

  firstFrame = false;
}

// Handle inputs depending on state
void Game::handleEvents() {
  if (state == STATE_RUNNING) {
    if (!digitalRead(LEFT_PIN))
      dino->crouch();

    if (!digitalRead(RIGHT_PIN) && digitalRead(RIGHT_PIN) != right_prev_state)
      dino->jump();

    if (digitalRead(LEFT_PIN) && digitalRead(LEFT_PIN) != left_prev_state)
      dino->stand();

    left_prev_state = digitalRead(LEFT_PIN);
    right_prev_state = digitalRead(RIGHT_PIN);
  } else {  // STATE_GAMEOVER OR STATE_MENU
    bool onMenu = true;

    while (onMenu) {

      if (!digitalRead(RIGHT_PIN) && digitalRead(RIGHT_PIN) != right_prev_state) {
        state = STATE_RUNNING;
        onMenu = false;
        gameStart = millis();
      }
      right_prev_state = digitalRead(RIGHT_PIN);
    }
    score = 0;
    firstFrame = true;
  }
}

// Reuse obstacles when they go out of bounds
void Game::renew(int entity) {
  score++;

  unsigned long t = millis() - gameStart;

  // min distance between obstacles is roughly 1/3 the distance traveled by the player in one jump
  int minDX = (0.6 + 0.000008 * t) * (10 * FRAMETIME);

  // try new position
  int px = SCREEN_WIDTH + rand() % 100;
  int model;

  if (entity == RENEW_CACTUS) {
    if (px - bird->getCollider().x < minDX)
      px = bird->getCollider().x + minDX;

    // cactus models 3 and 4 are bigger, spawn only after score 35
    if (score > 35)
      model = rand() % 4;
    else
      model = rand() % 2;

    cactus->renew(model, px);
  }

  else if (entity == RENEW_BIRD) {
    if (px - cactus->getCollider().x < minDX)
      px = cactus->getCollider().x + minDX;
    bird->renew(0, px);
  }
}

// Reset entities and change state to STATE_GAMEOVER
void Game::reset() {
  delete dino;
  dino = new Dino;
  delete bird;
  bird = new Bird;
  delete cactus;
  cactus = new Cactus;

  state = STATE_GAMEOVER;

  graphics->clear();
  graphics->render(0, 0, ASSET_GAMEOVER);
  graphics->renderText(125, 10, "score");
  graphics->renderText(150, 35, String(score));

  tone(BUZZER_PIN, 1000, 500);
  delay(500);
  noTone(BUZZER_PIN);

  checkScore();
}

// Check current score and save if necessary
void Game::checkScore() {
  fs::File file;

  if (score > maxScore) {
    maxScore = score;

    file = SPIFFS.open("/pontos.txt", "w");

    if (!file) {
      Serial.println("Couldn't open score file for writing");
      return;
    }

    file.println(std::to_string(score).c_str());

    file.close();
  }
}

// Return distance traveled based on time and basic physics
int Game::scrollBackground() {
  unsigned long long t = 0;
  t = millis() - gameStart;
  double x = 0, vx = 0, dx = 0;

  // x = v0t + at²/2
  x = 0.8 * t + 0.000004 * (t * t);
  // v = dx/dt = v0 + at
  vx = 0.8 + 0.000008 * t;
  dx = vx * deltaTime();

  return dx;
}

// Return deltaTime between current and last frame
unsigned long Game::deltaTime() {
  return (firstFrame) ? 0 : millis() - end;
}

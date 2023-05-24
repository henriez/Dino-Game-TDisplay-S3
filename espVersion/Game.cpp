#include <string>
#include "FS.h"
#include "Game.h"
#define FRAMETIME 40
#define STATE_MENU 1
#define STATE_RUNNING 2
#define STATE_GAMEOVER 3

#define RENEW_CACTUS 4
#define RENEW_BIRD 5

Game *Game::game = NULL;

Game::Game() {

  graphics = GraphicsManager::getInstance();
  Serial.begin(9600);
  if (!SPIFFS.begin()) {
    Serial.println("failed starting spiffs");
  }


  collision = CollisionManager::getInstance();
  dino = new Dino;
  bird = new Bird;
  cactus = new Cactus;
  state = STATE_MENU;
  start = end = right_prev_state = left_prev_state = points = 0;

  fs::File file = SPIFFS.open("/pontos.txt", "r");

  if (!file) {
    Serial.println("− failed to open file for reading");
    return;
  }

  Serial.println("− read max from file:");
  maxPoints = file.readString().toInt();
  Serial.printf("maxpoints: %d\n", maxPoints);
  file.close();

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
    int srcX = scrollBackground();  // como fazer essa na esp?
    handleEvents();
    dino->update();
    if (collision->collide(dino, cactus) || collision->collide(dino, bird))
      reset();
    if (collision->outOfBounds(cactus))
      renew(RENEW_CACTUS);
    if (collision->outOfBounds(bird))
      renew(RENEW_BIRD);
    graphics->renderText(10, 10, String(points));
    graphics->renderText(250, 10, "HI:");
    graphics->renderText(290, 10, String(maxPoints));
    graphics->renderBackground(srcX);
  } else if (state == STATE_GAMEOVER) {
    graphics->render(0, 0, GAMEOVER);
    graphics->renderText(125, 10, "Points");
    graphics->renderText(150, 35, String(points));
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

void Game::renew(int entity) {
  points++;
  unsigned long t = millis() - gameStart;
  int minDX = (0.6 + 0.000008 * t) * (10 * FRAMETIME);  // vx * dt (dt = tempo de ar do dino)

  end = millis() - gameStart;
  int px = SCREEN_WIDTH + rand() % 100;  // mudar logica de spawn
  int model;
  // define nova posicao e novo modelo de cacto
  if (entity == RENEW_CACTUS) {
    if (px - bird->getCollider().x < minDX)
      px = bird->getCollider().x + minDX;
    if (end > 50000) {
      model = rand() % 4;
    } else
      model = rand() % 2;

    cactus->renew(model, px);
  }
  // define nova posicao de passaro
  else if (entity == RENEW_BIRD) {
    if (px - cactus->getCollider().x < minDX)  // mudar valor para logica com tempo - alcance horizontal
      px = cactus->getCollider().x + minDX;    // minimo de distancia entre cada obstaculo
    bird->renew(0, px);
  }
}

void Game::reset() {
  delete dino;
  dino = new Dino;
  delete bird;
  bird = new Bird;
  delete cactus;
  cactus = new Cactus;
  state = STATE_GAMEOVER;

  //tone(BUZZER_PIN, 1000, 500);
  delay(500);
  //noTone(BUZZER_PIN);

  fs::File file;

  if (points > maxPoints) {
    maxPoints = points;
    file = SPIFFS.open("/pontos.txt", "w");
    if (!file) {
      Serial.println("− failed to open file for writing");
      return;
    }
    Serial.println(std::to_string(points).c_str());
    if (file.println(std::to_string(points).c_str())) {
      Serial.println("− file written");
    } else {
      Serial.println("− write failed");
    }

    file.close();
  }

  file = SPIFFS.open("/pontos.txt", "r");

  if (!file) {
    Serial.println("− failed to open file for reading");
    return;
  }

  Serial.println("− read from file:");
  Serial.println(file.readString());
  file.close();

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
  points = 0;
}

int Game::scrollBackground() {
  unsigned long long t = 0;
  t = millis() - gameStart;
  double x = 0, vx = 0, dx = 0;

  // x = v0t + at²/2
  x = 0.6 * t + 0.000004 * (t * t);
  // v = dx/dt = v0 + at
  vx = 0.6 + 0.000008 * t;
  dx = vx * deltaTime();
  int srcX = (int)(x) % 320;

  // graphics->render(0, 0, BACKGROUND, srcX); // nao sei se funciona na esp
  // criar sprite background e pushSprite em X negativo

  cactus->update(-dx);
  bird->update(-dx);

  return srcX;
}

unsigned long Game::deltaTime() {
  return millis() - end;
}

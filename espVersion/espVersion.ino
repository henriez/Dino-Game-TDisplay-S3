#include <iostream>
#include "Game.h"

Game* game;
void setup() {
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  game = Game::getInstance();
}

void loop() {
  game->run();
}

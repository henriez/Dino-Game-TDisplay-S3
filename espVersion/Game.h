#pragma once

#include "GraphicsManager.h"
#include "CollisionManager.h"
#include "Dino.h"
#include "Cactus.h"
#include "Bird.h"

// Macros for ESP32 pins
#define LEFT_PIN 43 
#define RIGHT_PIN 16
#define BUZZER_PIN 18

class Game {
public:
  // Destructor
  ~Game();

  // Singleton method
  static Game* getInstance();

  // Singleton method
  static void deleteInstance();

  // Main function inside Game, checks states, calls update, render and renew
  void run();

  // Handle inputs depending on state
  void handleEvents();

  // Reuse obstacles when they go out of bounds
  void renew(int entity);

  // Reset entities and change state to STATE_GAMEOVER
  void reset();

  // Check current score and save if necessary
  void checkScore();

  // Return distance traveled based on time and basic physics
  int scrollBackground();

  // Return deltaTime between current and last frame
  unsigned long deltaTime();

private:
  // Singleton requires private constructor
  Game();

  // Singleton static pointer
  static Game* game;
  
  // Managers
  GraphicsManager* graphics;
  CollisionManager* collision;

  // Entities
  Cactus* cactus;
  Bird* bird;
  Dino* dino;

  // Time handling variables
  unsigned long start, end, gameStart;

  // State handling variables
  int state, right_prev_state, left_prev_state;

  // Score handling variables
  int score, maxScore;

  // Used for dealing with background scroll and general entities movement 
  int px;
};
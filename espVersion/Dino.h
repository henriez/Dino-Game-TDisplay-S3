#pragma once

#include "Entity.h"

class Dino : public Entity {
public:
  // Contructor
  Dino();

  // Destructor
  ~Dino();

  // Updates position and state
  void update();

  // Render calling graphics manager
  void render();

  // Overriden method of Entity::getCollider(), returns different colliders based on state
  Collider getCollider() override;

  // Jump movement, called after input handling
  void jump();

  // Crouch movement, called after input handling
  void crouch();

  // Stand movement, called after input handling
  void stand();
private:
  // State changes behavior
  int state;

  // Used for dealing with gravity
  float ySpeed;
};
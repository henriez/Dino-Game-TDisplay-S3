#pragma once

#include "Collider.h"

// Cactus, Bird and Dino's parent class
class Entity {
public:
  // Constructor
  Entity() : collider(nullptr) {}

  // Destructor
  ~Entity() {}

  // Render abstract method
  virtual void render() = 0;

  // Returns collider
  virtual Collider getCollider() {
    return *collider;
  }

  // Renew abstract method - redefined in Cactus and Bird
  virtual void renew(int info, int px) {}
protected:
  // Collider for dealing with collisions
  Collider* collider;
};
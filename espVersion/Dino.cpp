#include "Dino.h"
#include "GraphicsManager.h"

#define gravity 2

// Macros for state handling
#define STATE_GROUND 1
#define STATE_CROUCH 2
#define STATE_AIR 3

// Constructor
Dino::Dino() {
  collider = new Collider(40, 80, 54, 54);
  state = STATE_GROUND;
  ySpeed = 0;
}

// Destructor
Dino::~Dino() {
  delete collider;
}

// Updates position and state
void Dino::update() {

  collider->y += ySpeed;
  if (collider->y > 80) {
    collider->y = 80;
    state = STATE_GROUND;
    ySpeed = 0;
  }
  if (state == STATE_AIR)
    ySpeed += gravity;

}

// Render calling graphics manager
void Dino::render() {
  if (state == STATE_CROUCH)
    GraphicsManager::getInstance()->render(collider->x, collider->y + 27, STATE_CROUCH);
  else
    GraphicsManager::getInstance()->render(collider->x, collider->y, ASSET_DINO);
}

// Overriden method of Entity::getCollider(), returns different colliders based on state
Collider Dino::getCollider() {
  Collider col = *collider;
  if (state == STATE_CROUCH) {
    col.h /= 2;
    col.y += 27;
  }
  return col;
}

// Crouch movement, called after input handling
void Dino::crouch() {
  if (state == STATE_GROUND)
    state = STATE_CROUCH;
}

// Stand movement, called after input handling
void Dino::stand() {
  if (state == STATE_CROUCH)
    state = STATE_GROUND;
}

// Jump movement, called after input handling
void Dino::jump() {
  if (state != STATE_AIR) {
    state = STATE_AIR;
    ySpeed = -15;
  }
}

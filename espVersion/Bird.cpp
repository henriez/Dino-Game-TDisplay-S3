#include "Bird.h"
#include "GraphicsManager.h"

// Constructor
Bird::Bird(int y) {
  collider = new Collider(480, y, 42, 32);
}

// Destructor
Bird::~Bird() {
  delete collider;
}

// Update position based on traveled distance received
void Bird::update(double dx) {
  collider->x += dx;
}

// Render calling graphics manager
void Bird::render() {
  GraphicsManager::getInstance()->render(collider->x, collider->y, ASSET_BIRD);
}

// Renew based on new height and position
void Bird::renew(int info, int px) {
  collider->x = px;
  int h = rand() % 3;
  if (h == 0) collider->y = HEIGHT1;
  if (h == 1) collider->y = HEIGHT2;
  if (h == 2) collider->y = HEIGHT3;
}

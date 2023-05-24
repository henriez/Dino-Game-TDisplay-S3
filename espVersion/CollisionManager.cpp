#include "CollisionManager.h"

CollisionManager *CollisionManager::manager = NULL;

CollisionManager::CollisionManager() {
}

CollisionManager::~CollisionManager() {
}

CollisionManager *CollisionManager::getInstance() {
  if (!manager)
    manager = new CollisionManager;
  return manager;
}

void CollisionManager::deleteInstance() {
  if (manager)
    delete manager;
}

bool CollisionManager::collide(Entity *en1, Entity *en2) {
  Collider c1 = en1->getCollider();
  Collider c2 = en2->getCollider();

  return (AABB(c1, c2));
}

bool CollisionManager::outOfBounds(Entity *en) {
  Collider c = en->getCollider();
  return (c.x + c.w < 0);  // if its out of bounds, regenerates cactus or bird
}

bool CollisionManager::AABB(Collider c1, Collider c2) {
  return (c1.x + c1.w > c2.x && c2.x + c2.w > c1.x && c1.y + c1.h > c2.y && c2.y + c2.h > c1.y);
}
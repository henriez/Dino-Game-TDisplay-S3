#pragma once

#include "Entity.h"

class CollisionManager {
public:
  // Destructor
  ~CollisionManager();

  // Singleton method
  static CollisionManager* getInstance();

  // Singleton method
  static void deleteInstance();

  // Returns if entities are colliding using AABB algorithm
  bool collide(Entity* en1, Entity* en2);

  // Returns if entity is out of the screen (used with Bird and Cactus)
  bool outOfBounds(Entity* en);

private:
  // Singleton requires private constructor
  CollisionManager();

  // Singleton static pointer
  static CollisionManager* manager;

  // Axis Aligned Bounding Boxes algorithm for detecting collisions
  bool AABB(Collider c1, Collider c2);
};
#pragma once

#include <iostream>
#include "Entity.h"

class CollisionManager
{
public:
    ~CollisionManager();

    static CollisionManager *getInstance();
    static void deleteInstance();

    bool collide(Entity* en1, Entity* en2);
    bool outOfBounds(Entity* en);

private:
    CollisionManager();
    static CollisionManager *manager;
    bool AABB(Collider c1, Collider c2);
};
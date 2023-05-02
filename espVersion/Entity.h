#pragma once

#include "Collider.h"

class Entity{
public:
    Entity();
    ~Entity();

    virtual void render() = 0;
    Collider getCollider() { return *collider; }
    virtual void renew() {}
protected:
    Collider* collider;    
};
#pragma once

#include "Collider.h"

class Entity{
public:
    Entity();
    ~Entity();

    virtual void render() = 0;
    virtual void renew() {}
    Collider getCollider() { return *collider; }
protected:
    Collider* collider;    
};
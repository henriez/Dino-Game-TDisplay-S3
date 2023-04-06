#pragma once

#include "Collider.h"
#include <iostream>

class Entity{
public:
    Entity();
    ~Entity();

    virtual void render() = 0;
    virtual void update() = 0;
protected:
    Collider* collider;    
};
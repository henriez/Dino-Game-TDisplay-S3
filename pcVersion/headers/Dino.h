#pragma once

#include "Entity.h"

class Dino : public Entity{
public:
    Dino();
    ~Dino();
    void render();
    void update();

    void jump();
    void crouch();
private:
    bool inAir;
    float ySpeed;
};
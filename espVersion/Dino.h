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
    void stand();
private:
    int state;
    float ySpeed;
};
#pragma once

#include "Entity.h"

class Bird : public Entity{
public:
    Bird();
    ~Bird();
    void render();
    void update();

private:
    float xSpeed;
};
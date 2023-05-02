#pragma once

#include "Entity.h"

#define HEIGHT1 10
#define HEIGHT2 25
#define HEIGHT3 40

class Bird : public Entity{
public:
    Bird(int y = HEIGHT1);
    ~Bird();
    void render();
    void update(double dx);
    void renew() override;

private:
    int initialPosition;
    float xSpeed;
};
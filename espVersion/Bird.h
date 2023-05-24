#pragma once

#include "Entity.h"

#define HEIGHT1 10
#define HEIGHT2 35
#define HEIGHT3 60

class Bird : public Entity{
public:
    Bird(int y = HEIGHT1);
    ~Bird();
    void render();
    void update(double dx);
    void renew(int info, int px) override;

private:
    int initialPosition;
    float xSpeed;
};
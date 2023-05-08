#pragma once

#include "Entity.h"

#define HEIGHT1 80
#define HEIGHT2 95
#define HEIGHT3 110

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
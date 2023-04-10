#pragma once

#include "Entity.h"

class Cactus : public Entity{
public:
    Cactus();
    ~Cactus();
    void render();
    void update();
    void updateCactus (int x);

private:
    int initialPosition;
};
#pragma once

#include "Entity.h"

#define CACTUS_MODEL_1 1
#define CACTUS_MODEL_2 2
#define CACTUS_MODEL_3 3
#define CACTUS_MODEL_4 4

class Cactus : public Entity{
public:
    Cactus(int model = CACTUS_MODEL_1);
    ~Cactus();
    void render();
    void update(double dx);
    void renew() override;

private:
    int initialPosition;
    int model;
};
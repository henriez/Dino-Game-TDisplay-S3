#include "Dino.h"
#include "GraphicsManager.h"

#define gravity 2

#define GROUND 1
#define CROUCH 2
#define AIR 3

Dino::Dino()
{
    collider = new Collider(40, 80, 54, 54);
    state = GROUND;
    ySpeed = 0;
}

Dino::~Dino()
{
    delete collider;
}

// PC version
void Dino::update()
{

    collider->y += ySpeed;
    if (collider->y > 80)
    {
        collider->y = 80;
        state = GROUND;
        ySpeed = 0;
    }
    if (state == AIR)
        ySpeed += gravity;

    render();
}

// ESP32 version
/*
void Dino::update(){

}*/

void Dino::render()
{
    if (state == CROUCH)
        GraphicsManager::getInstance()->render(collider->x, collider->y + 27, CROUCH);
    else
        GraphicsManager::getInstance()->render(collider->x, collider->y, DINO);
}

void Dino::crouch()
{
    state = CROUCH;
}

void Dino::stand()
{
    state = GROUND;
}

void Dino::jump()
{
    if (state != AIR)
    {
        state = AIR;
        ySpeed = -15;
    }
}

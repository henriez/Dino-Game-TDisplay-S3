#include "headers/Dino.h"
#include "headers/GraphicsManager.h"

#define gravity 2

Dino::Dino()
{
    collider = new Collider(40, 40, 90, 90);
    inAir = false;
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
    if (collider->y > 40)
    {
        collider->y = 40;
        inAir = false;
        ySpeed = 0;
    }
    if (inAir)
        ySpeed += gravity;

    render();
}

// ESP32 version
/*
void Dino::update(){

}*/

void Dino::render()
{
    GraphicsManager::getInstance()->render(collider->x, collider->y, "dino");
}

void Dino::crouch()
{
}

void Dino::jump()
{
    if (!inAir)
    {
        inAir = true;
        ySpeed = -15;
    }
}

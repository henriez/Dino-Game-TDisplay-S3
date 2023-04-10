#include "headers/Bird.h"
#include "headers/GraphicsManager.h"

Bird::Bird()
{
    collider = new Collider(270, -10, 50, 50);
    xSpeed = -5;
}

Bird::~Bird()
{
    delete collider;
}

// PC version
void Bird::update()
{
    collider->x += xSpeed;
    render();
}

// ESP32 version
/*
void Bird::update(){

}*/

void Bird::render()
{
    GraphicsManager::getInstance()->render(collider->x, collider->y, "dino");
}
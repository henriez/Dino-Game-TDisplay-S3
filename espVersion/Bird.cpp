#include "Bird.h"
#include "GraphicsManager.h"

Bird::Bird(int y)
{
    collider = new Collider(SCREEN_WIDTH, y, 42, 32);
    xSpeed = -5;
    initialPosition = 1.5*SCREEN_WIDTH;
}

Bird::~Bird()
{
    delete collider;
}

void Bird::update(double dx)
{
    collider->x = initialPosition + dx;
    render();
}

void Bird::render()
{
    GraphicsManager::getInstance()->render(collider->x, collider->y, BIRD);
}

void Bird::renew(){
    collider->x = rand()%100 + SCREEN_WIDTH;
    initialPosition += collider->x;
    int h = rand()%3;
    if (h == 0) collider->y = HEIGHT1;
    if (h == 1) collider->y = HEIGHT2;
    if (h == 2) collider->y = HEIGHT3;
}
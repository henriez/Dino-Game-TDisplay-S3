#include "Bird.h"
#include "GraphicsManager.h"

Bird::Bird(int y)
{
    collider = new Collider(480, y, 42, 32);
    xSpeed = -5;
}

Bird::~Bird()
{
    delete collider;
}

void Bird::update(double dx)
{
    collider->x += dx;
    render();
}

void Bird::render()
{
    GraphicsManager::getInstance()->render(collider->x, collider->y, BIRD);
}

void Bird::renew(int info, int px){
    collider->x = px;
    int h = rand()%3;
    if (h == 0) collider->y = HEIGHT1;
    if (h == 1) collider->y = HEIGHT2;
    if (h == 2) collider->y = HEIGHT3;
}

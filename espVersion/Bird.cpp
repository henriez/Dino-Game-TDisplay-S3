#include "Bird.h"
#include "GraphicsManager.h"

Bird::Bird(int y)
{
    collider = new Collider(SCREEN_WIDTH, y, 42, 32);
    xSpeed = -5;
}

Bird::~Bird()
{
    delete collider;
}

void Bird::update()
{
    collider->x += xSpeed;
    render();
}

void Bird::render()
{
    GraphicsManager::getInstance()->render(collider->x, collider->y, BIRD);
}
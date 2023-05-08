#include "Dino.h"
#include "GraphicsManager.h"

#define gravity 2

#define GROUND 1
#define CROUCH 2
#define AIR 3

Dino::Dino()
{
    collider = new Collider(40, 36, 54, 54);
    state = GROUND;
    ySpeed = 0;
}

Dino::~Dino()
{
    delete collider;
}

void Dino::update()
{

    collider->y += ySpeed;
    if (collider->y < 36)
    {
        collider->y = 36;
        state = GROUND;
        ySpeed = 0;
    }
    if (state == AIR)
        ySpeed -= gravity;

    render();
}

void Dino::render()
{
    if (state == CROUCH)
        GraphicsManager::getInstance()->render(collider->x, collider->y, CROUCH);
    else
        GraphicsManager::getInstance()->render(collider->x, collider->y, DINO);
}

Collider Dino::getCollider(){
  Collider col = *collider;
  if (state == CROUCH){
    col.h /= 2;
  }
  return col;
}

void Dino::crouch()
{
    if (state == GROUND)
        state = CROUCH;
}

void Dino::stand()
{
    if (state == CROUCH)
        state = GROUND;
}

void Dino::jump()
{
    if (state != AIR)
    {
        state = AIR;
        ySpeed = 15;
    }
}

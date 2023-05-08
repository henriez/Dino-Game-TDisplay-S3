#include "Cactus.h"
#include "GraphicsManager.h"

Cactus::Cactus(int model)
{
    this->model = model;
    switch (model)
    {
    case CACTUS_MODEL_1:
        collider = new Collider(320, 36, 11, 24);
        break;
    case CACTUS_MODEL_2:
        collider = new Collider(320, 36, 18, 36);
        break;
    case CACTUS_MODEL_3:
        collider = new Collider(320, 36, 50, 36);
        break;
    case CACTUS_MODEL_4:
        collider = new Collider(320, 36, 35, 36);
        break;
    default:
        break;
    }
    initialPosition = 320;
}

Cactus::~Cactus()
{
    delete collider;
}

void Cactus::update(double dx) 
{
    collider->x = initialPosition + dx;
    render();
}


void Cactus::render()
{
    switch (model)
    {
    case CACTUS_MODEL_1:
        GraphicsManager::getInstance()->render(collider->x, collider->y, CACTUS1);
        break;
    case CACTUS_MODEL_2:
        GraphicsManager::getInstance()->render(collider->x, collider->y, CACTUS2);
        break;
    case CACTUS_MODEL_3:
        GraphicsManager::getInstance()->render(collider->x, collider->y, CACTUS3);
        break;
    case CACTUS_MODEL_4:
        GraphicsManager::getInstance()->render(collider->x, collider->y, CACTUS4);
        break;
    default:
        break;
    }
    
}

void Cactus::renew(int info, int px)
{
   
    delete collider;
    if (info == 0)
        model = CACTUS_MODEL_1;
    else if (info == 1)
        model = CACTUS_MODEL_2;
    else if (info == 2)
        model = CACTUS_MODEL_3;
    else if (info == 3)
        model = CACTUS_MODEL_4;
    switch (model)
    {
    case CACTUS_MODEL_1:
        collider = new Collider(320, 36, 11, 24);
        break;
    case CACTUS_MODEL_2:
        collider = new Collider(320, 36, 18, 36);
        break;
    case CACTUS_MODEL_3:
        collider = new Collider(320, 36, 50, 36);
        break;
    case CACTUS_MODEL_4:
        collider = new Collider(320, 36, 35, 36);
        break;
    default:
        break;
    }
    // initialPosition += rand()%100 + SCREEN_WIDTH;
}
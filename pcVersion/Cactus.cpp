#include "headers/Cactus.h"
#include "headers/GraphicsManager.h"

Cactus::Cactus()
{
    collider = new Collider(280, 40, 40, 60);
    initialPosition=280;
}

Cactus::~Cactus()
{
    delete collider;
}

// PC version
void Cactus::update(){}
void Cactus::updateCactus(int x) //CACTO VOLTAR SRC COM RELAÇÃO A POSIÇÃO INICIAL E NÃO +=
{
    collider->x=initialPosition+x;
    render();
}

// ESP32 version
/*
void Bird::update(){

}*/

void Cactus::render()
{
    GraphicsManager::getInstance()->render(collider->x, collider->y, "dino");
}

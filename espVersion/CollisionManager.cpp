#include "CollisionManager.h"

CollisionManager *CollisionManager::manager = NULL;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

CollisionManager *CollisionManager::getInstance()
{
    if (!manager)
        manager = new CollisionManager;
    return manager;
}

void CollisionManager::deleteInstance()
{
    if (manager)
        delete manager;
}
#include "headers/GraphicsManager.h"

GraphicsManager *GraphicsManager::manager = nullptr;

GraphicsManager::GraphicsManager() {}

GraphicsManager::~GraphicsManager() {}

GraphicsManager *GraphicsManager::getInstance()
{
    if (!manager)
        manager = new GraphicsManager();

    return manager;
}

void GraphicsManager::deleteInstance()
{
    if (manager)
        delete manager;
}
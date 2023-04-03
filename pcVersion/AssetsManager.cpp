#include "headers/AssetsManager.h"

AssetsManager *AssetsManager::manager = nullptr;

AssetsManager::AssetsManager() {}

AssetsManager::~AssetsManager() {}

AssetsManager *AssetsManager::getInstance()
{
    if (!manager)
        manager = new AssetsManager();

    return manager;
}

void AssetsManager::deleteInstance()
{
    if (manager)
        delete manager;
}

short *AssetsManager::getAssets(string assetName)
{
    return assets[assetName];
}
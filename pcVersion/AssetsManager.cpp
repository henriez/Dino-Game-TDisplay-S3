#include "headers/AssetsManager.h"

AssetsManager *AssetsManager::manager = nullptr;

AssetsManager::AssetsManager()
{
    Asset *tmpAsset;
    tmpAsset = new Asset("dino");
    assets.emplace("dino", tmpAsset);
}

AssetsManager::~AssetsManager()
{
    map<string, Asset *>::iterator i;
    for (i = assets.begin(); i != assets.end(); i++)
    {
        delete i->second;
    }
}

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

/*short *AssetsManager::getAsset(string assetName)
{
    return assets[assetName];
}*/
// ESP32 version

Asset *AssetsManager::getAsset(string assetName)
{
    return assets[assetName];
} // PC Version
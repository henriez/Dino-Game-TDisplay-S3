#include "AssetsManager.h"

#include "background.h"
#include "bird.h"
#include "cactus1.h"
#include "cactus2.h"
#include "cactus3.h"
#include "cactus4.h"
#include "crouch.h"
#include "menu.h"
#include "trex.h"

AssetsManager *AssetsManager::manager = NULL;

AssetsManager::AssetsManager()
{
    Asset *tmpAsset;
    tmpAsset = new Asset(trex, 54, 54);
    assets.insert(std::make_pair("dino", tmpAsset));
    tmpAsset = new Asset(crouch, 54, 27);
    assets.insert(std::make_pair("crouch", tmpAsset));

    tmpAsset = new Asset(bird, 42, 32);
    assets.insert(std::make_pair("bird", tmpAsset));

    tmpAsset = new Asset(cactus1, 11, 24);
    assets.insert(std::make_pair("cactus1", tmpAsset));
    tmpAsset = new Asset(cactus2, 18, 36);
    assets.insert(std::make_pair("cactus2", tmpAsset));
    tmpAsset = new Asset(cactus3, 50, 36);
    assets.insert(std::make_pair("cactus3", tmpAsset));
    tmpAsset = new Asset(cactus4, 35, 36);
    assets.insert(std::make_pair("cactus4", tmpAsset));

    tmpAsset = new Asset(menu, 320, 170);
    assets.insert(std::make_pair("menu", tmpAsset));
    tmpAsset = new Asset(background, 320, 170);
    assets.insert(std::make_pair("background", tmpAsset));
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

Asset *AssetsManager::getAsset(string assetName)
{
    return assets[assetName];
}
// ESP32 version
#pragma once
#include <map>
#include <string>
#include "Asset.h"

using namespace std;


class AssetsManager
{
public:
    
    ~AssetsManager();

    static AssetsManager* getInstance();
	static void deleteInstance();

    //short* getAsset(string assetName); // ESP32 version
    Asset* getAsset(string assetName); // PC version

private:
    AssetsManager();
    static AssetsManager* manager;
    //map<string, short*> assets; // ESP32 version
    map<string, Asset*> assets; // PC version
};
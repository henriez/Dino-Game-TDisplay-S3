#pragma once
#include <map>
#include <string>

using namespace std;


class AssetsManager
{
public:
    
    ~AssetsManager();

    static AssetsManager* getInstance();
	static void deleteInstance();

    short* getAssets(string assetName);

private:
    AssetsManager();
    static AssetsManager* manager;
    map<string, short*> assets;
};
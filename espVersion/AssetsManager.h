#pragma once
#include <map>
#include <string>
#include "Asset.h"

using namespace std;


class AssetsManager {
public:

  ~AssetsManager();

  static AssetsManager* getInstance();
  static void deleteInstance();

  Asset* getAsset(string assetName);

private:
  AssetsManager();
  static AssetsManager* manager;
  std::map<string, Asset*> assets;
};
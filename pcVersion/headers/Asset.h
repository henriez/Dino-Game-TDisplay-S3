#pragma once
#include <string> // only for PC

/*// ESP32 version
class Asset
{
public:
    Asset() { bmp = nullptr; }
    Asset(unsigned short *p) : bmp(p) {}
    ~Asset() {}

    unsigned short *getBMP() const
    {
        return bmp;
    }
    int getW() { return width; }
    int getH() { return height; }

private:
    unsigned short *bmp;
    int width;
    int height;
};*/

class Asset
{
public:
    Asset() {}
    ~Asset() {}
    std::string getPath() { return path; }

    int getW() { return width; }
    int getH() { return height; }

private:
    std::string path;
    int width;
    int height;
};
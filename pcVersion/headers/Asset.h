#pragma once
#include <string> // only for PC
using namespace std;

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
    Asset(string filepath = "", int w = 10, int h = 10) : path(filepath), width(w), height(h) {}
    ~Asset() {}
    string getPath() { return path; }
    int getH() { return height; }
    int getW() { return width; }

private:
    string path;
    int width;
    int height;
};
#pragma once
using namespace std;
#include <string>

// ESP32 version

class Asset
{
public:
    //Asset(const unsigned short* bitmap, int w = 10, int h = 10) : width(w), height(h), bmp(bitmap) {} // esp32
    Asset(const char* filepath = "", int w = 10, int h = 10) : width(w), height(h), path(filepath) {} // pc
    ~Asset() {}
    //const unsigned short* getBMP() { return bmp; } // esp32
    const char* getPath() { return path; }
    const int getH() { return height; }
    const int getW() { return width; }

private:
    //const unsigned short *bmp; // esp32
    const char* path; // pc
    const int width;
    const int height;
};
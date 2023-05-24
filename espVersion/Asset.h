#pragma once
using namespace std;

// ESP32 version

class Asset
{
public:
    Asset(const unsigned short* bitmap, int w = 10, int h = 10) : width(w), height(h), bmp(bitmap) {}
    ~Asset() {}
    const unsigned short* getBMP() { return bmp; }
    const int getH() { return height; }
    const int getW() { return width; }

private:
    const unsigned short *bmp;
    const int width;
    const int height;
};
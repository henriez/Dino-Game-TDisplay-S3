#pragma once

// Asset class storing a bitmap pointer, along with width and height informations

class Asset {
public:
  // Constructor
  Asset(const unsigned short* bitmap, int w = 10, int h = 10) : width(w), height(h), bmp(bitmap) {}

  // Destructor
  ~Asset() {}

  // Returns cons bitmap pointer
  const unsigned short* getBMP() {
    return bmp;
  }

  // Returns asset height
  const int getH() {
    return height;
  }

  // Returns asset width
  const int getW() {
    return width;
  }

private:
  // const attributes
  const unsigned short* bmp;
  const int width;
  const int height;
};
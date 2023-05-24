#pragma once

// Collider class for handling collisions

class Collider {
public:
  // Constructor
  Collider(float x0, float y0, int w0, int h0) : x(x0), y(y0), w(w0), h(h0) {}
  
  // Destructor
  ~Collider() {}

  // Position (x,y), width (w) and height (h)
  float x;
  float y;
  int w;
  int h;
};
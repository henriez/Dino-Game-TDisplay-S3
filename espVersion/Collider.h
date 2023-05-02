#pragma once

class Collider
{
public:
    Collider(float x0, float y0, int w0, int h0) : x(x0), y(y0), w(w0), h(h0) {}
    ~Collider(){}
    float x;
    float y;
    const int w;
    const int h;
};
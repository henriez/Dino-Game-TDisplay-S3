#pragma once

#include <iostream>

class CollisionManager
{
public:
    ~CollisionManager();

    static CollisionManager *getInstance();
    static void deleteInstance();

private:
    CollisionManager();
    static CollisionManager *manager;
};
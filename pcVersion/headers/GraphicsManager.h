#pragma once
#include <map>
#include <string>

using namespace std;


class GraphicsManager
{
public:
    ~GraphicsManager();

    static GraphicsManager* getInstance();
	static void deleteInstance();

    void render(int x, int y, string asset);
    void clear();

private:
    GraphicsManager();
    static GraphicsManager* manager;
};
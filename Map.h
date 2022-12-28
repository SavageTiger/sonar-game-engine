#ifndef MAP_H
#define MAP_H

#include "Textures.h"
#include <vector>

#define TILE_SIZE 64

class Map {
private:
    bool mapLoaded = false;
    std::vector<std::vector<int>> layout;

    void loadMap(const char* mapName);
    static void renderFloor(int row, int column, Textures* textures);
    void renderWall(int row, int column, Textures* textures);

public:
    void renderMap(const char* mapName, Textures* textures);
    bool isWall(int x, int y, short margin = 0);
    float wallThickness(int row, int column);
    int getTextureId(float x, float y);

};
#endif
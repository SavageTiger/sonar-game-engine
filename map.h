#ifndef MAP_H
#define MAP_H

#include "textures.h"
#include <vector>

#define TILE_SIZE 64

class map {
private:
    bool mapLoaded = false;
    std::vector<std::vector<int>> layout;

    void loadMap(const char* mapName);
    static void renderFloor(int row, int column, textures* textures);
    void renderWall(int row, int column, textures* textures);

public:
    void renderMap(const char* mapName, textures* textures);
    bool isWall(float x, float y);
    int getTextureId(float x, float y);


};

#endif
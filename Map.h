#ifndef MAP_H
#define MAP_H

#include "MapTile.h"
#include "Textures.h"
#include <vector>

#define TILE_SIZE 64

class Map {
private:
    bool mapLoaded = false;

    std::vector<std::vector<MapTile>> layout;
    std::vector<MapTile*> activeDoors;

    static void renderFloor(int row, int column, Textures* textures);
    void renderWall(int row, int column, Textures* textures);

public:
    void loadMap(const char* mapName);
    bool isWall(int x, int y, short margin = 0);
    bool openDoor(int x, int y);
    bool animateDoors();
    float wallThickness(int row, int column);
    int getTextureId(float x, float y);

};
#endif
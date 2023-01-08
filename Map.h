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

    void swapEndianness(char* data, size_t size);

public:
    void loadMap(const char* mapName, Textures* textures);
    bool isWall(int x, int y, short margin = 0);
    MapTile* getMapTile(int x, int y);
    void openDoor(int x, int y);
    bool animateDoors();

    // FOR DEBUGGING
    void renderTiles(Textures* textures);
};
#endif
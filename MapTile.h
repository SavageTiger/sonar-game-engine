#ifndef SONAR_MAPTILE_H
#define SONAR_MAPTILE_H


class MapTile {
private:
    short tileType;
    bool doorOpen;
    double doorOpenRatio;

public:
    const short TILE_TYPE_FLOOR = 0;
    const short TILE_TYPE_WALL = 1;
    const short TILE_TYPE_DOOR = 2;

    MapTile(short paramTileType);

    bool isFloor();
    bool isWall();
    bool isDoor();

    bool isOpenDoor();
    bool isFullyOpenDoor();
    void openDoor();
    void increaseDoorOpenRatio();
    float getDoorOpenRatio();
    float thickness();
    short getTextureId();
};


#endif
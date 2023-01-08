#ifndef SONAR_MAPTILE_H
#define SONAR_MAPTILE_H


class MapTile {
private:
    short tileType;
    short wallTextureId;
    short floorTextureId;
    short ceilingTextureId;
    float thickness;
    bool doorOpen;
    double doorOpenRatio;

public:
    const short TILE_TYPE_FLOOR = 1;
    const short TILE_TYPE_WALL = 2;
    const short TILE_TYPE_DOOR = 3;

    MapTile(short paramTileType, short paramTileTextureId, short paramFloorTextureId, short ceilingTextureId, float thickness);

    bool isFloor();
    bool isWall();
    bool isDoor();

    bool isOpenDoor();
    bool isFullyOpenDoor();
    void openDoor();
    void increaseDoorOpenRatio();
    float getDoorOpenRatio();
    float getThickness();
    short getWallTextureId();
    short getFloorTextureId();
    short getCeilingTextureId();
};


#endif
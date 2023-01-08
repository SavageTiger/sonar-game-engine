#include "MapTile.h"

MapTile::MapTile(short paramTileType, short paramTileTextureId, short paramFloorTextureId, short paramCeilingTextureId, float paramThickness)
{
    tileType = paramTileType;
    wallTextureId = paramTileTextureId;
    floorTextureId = paramFloorTextureId;
    ceilingTextureId = paramCeilingTextureId;
    thickness = paramThickness;
    doorOpen = false;
}

bool MapTile::isFloor()
{
    return tileType == TILE_TYPE_FLOOR;
}

bool MapTile::isWall()
{
    return tileType == TILE_TYPE_WALL;
}

bool MapTile::isDoor()
{
    return tileType == TILE_TYPE_DOOR;
}

bool MapTile::isOpenDoor()
{
    return doorOpen;
}

bool MapTile::isFullyOpenDoor()
{
    return doorOpenRatio > .9;
}

void MapTile::openDoor()
{
    doorOpen = true;
    doorOpenRatio = 0;
}

void MapTile::increaseDoorOpenRatio()
{
    if (doorOpenRatio < .9) {
        doorOpenRatio += 0.010;
    }
}

float MapTile::getDoorOpenRatio()
{
    return doorOpenRatio;
}

float MapTile::getThickness()
{
    return this->thickness;
}

short MapTile::getWallTextureId()
{
    return this->wallTextureId;
}

short MapTile::getFloorTextureId()
{
    return this->floorTextureId;
}

short MapTile::getCeilingTextureId()
{
    return this->ceilingTextureId;
}

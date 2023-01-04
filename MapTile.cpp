#include "MapTile.h"
#include <thread>

MapTile::MapTile(short paramTileType)
{
    tileType = paramTileType;
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

float MapTile::thickness()
{
    return this->isDoor() ? 0.4 : 1;
}

short MapTile::getTextureId()
{
    return this->isDoor() ? 4 : 0;
}

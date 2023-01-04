#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include "Map.h"
#include "Textures.h"

/*void Map::renderWall(int row, int column, Textures* textures) {
    glEnable(GL_TEXTURE_2D);

    textures->loadTexture(0);

    int x = column * TILE_SIZE;
    int y = row * TILE_SIZE;

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2i(x, y);
    glTexCoord2f(1, 0);
    glVertex2i(x + TILE_SIZE, y);
    glTexCoord2f(1, 1);
    glVertex2i(x + TILE_SIZE, y + TILE_SIZE);
    glTexCoord2f(0, 1);
    glVertex2i(x, y + TILE_SIZE);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Map::renderFloor(int row, int column, Textures* textures) {
    glEnable(GL_TEXTURE_2D);

    textures->loadTexture(1);

    int x = column * TILE_SIZE;
    int y = row * TILE_SIZE;

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(x, y);
    glTexCoord2i(1, 0);
    glVertex2i(x + TILE_SIZE, y);
    glTexCoord2i(1, 1);
    glVertex2i(x + TILE_SIZE, y + TILE_SIZE);
    glTexCoord2i(0, 1);
    glVertex2i(x, y + TILE_SIZE);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void Map::renderMap(const char* mapName, Textures* textures) {
    if (mapLoaded == false) {
        Map::loadMap(mapName);

        mapLoaded = true;
    }

    for (int r = 0; r < layout.size(); r++) {
        for (int c = 0; c < layout[r].size(); c++) {
            switch (layout[r][c]) {
                case 48:
                    Map::renderFloor(r, c, textures);
                    break;

                case 49:
                case 50:
                    Map::renderWall(r, c, textures);
                    break;
            }
        }
    }
}*/

bool Map::isWall(int x, int y, short margin)
{
    if (margin > 0 && (
        isWall(x - margin, y - margin) == true ||
        isWall(x + margin, y - margin) == true ||
        isWall(x - margin, y + margin) == true ||
        isWall(x + margin, y + margin) == true)
    ) {
        return true;
    }

    MapTile* mapTile = this->getMapTile(x, y);

    if (mapTile == nullptr) {
        return false;
    }

    if (mapTile->isFloor()) {
        return false;
    }

    if (mapTile->isDoor() && mapTile->isFullyOpenDoor()) {
        return false;
    }

    return true;
}

bool Map::openDoor(int x, int y)
{
    short column = x / TILE_SIZE;
    short row = y / TILE_SIZE;

    short rowCount = layout.size();
    short columnCount = layout[row].size();

    std::vector<MapTile*> possibleDoors;

    possibleDoors.push_back(&layout[row][column]);

    if (row != 0) {
        possibleDoors.push_back(&layout[row - 1][column]);
    }

    if (row + 1 <= rowCount) {
        possibleDoors.push_back(&layout[row + 1][column]);
    }

    if (column != 0) {
        possibleDoors.push_back(&layout[row][column - 1]);
    }

    if (column + 1 <= columnCount) {
        possibleDoors.push_back(&layout[row][column + 1]);
    }

    for (auto& possibleDoor : possibleDoors) {
        if (possibleDoor->isDoor() && possibleDoor->isOpenDoor() == false) {
            possibleDoor->openDoor();

            activeDoors.push_back(possibleDoor);
        }
    }
}

MapTile* Map::getMapTile(int x, int y)
{
    short column = x / TILE_SIZE;
    short row = y / TILE_SIZE;

    if (row < 0 || column < 0) {
        return nullptr;
    }

    if (row >= layout.size()) {
        return nullptr;
    }

    if (column >= layout[row].size()) {
        return nullptr;
    }

    return &layout[row][column];
}

bool Map::animateDoors()
{
    for (auto& door : activeDoors) {
        door->increaseDoorOpenRatio();

        if (door->isFullyOpenDoor()) {
            activeDoors.pop_back();
        }
    }

    return activeDoors.size() > 0;
}

void Map::loadMap(const char* mapName) {
    char fileChar;
    char mapPath[128] = {0};

    short row = 0;
    short column = 0;

    snprintf(mapPath, 128, "./maps/%s.map", mapName);

    FILE *file = fopen(mapPath, "r");

    if (file == nullptr) {
        printf("Unable to read map %s.map", mapName);

        exit(1);
    }

    do {
        fileChar = fgetc(file);

        if (row >= layout.size()) {
            layout.push_back({});
        }

        if (fileChar == 49 || fileChar == 48 || fileChar == 50) {
            MapTile mapTile = MapTile(atoi(&fileChar));

            layout[row].push_back(mapTile);

            column++;
        }

        if (fileChar == 10) {
            column = 0;

            row++;
        }
    } while (fileChar != EOF);
}


#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <arpa/inet.h>
#include "Map.h"
#include "Textures.h"
#include <GL/gl.h>

void Map::renderTiles(Textures* textures)
{
    glEnable(GL_TEXTURE_2D);

    for (int row = 0; row < layout.size(); row++) {
        for (int column = 0; column < layout[row].size(); column++) {
            MapTile tile = layout[row][column];

            textures->prepTexture(tile.getWallTextureId());

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
        }
    }

    glDisable(GL_TEXTURE_2D);
}

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

void Map::openDoor(int x, int y)
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

void Map::loadMap(const char* mapName, Textures* textures) {
    bool bigEndian = (htonl(47) == 47);
    char mapPath[128] = {0};

    short row = 0;

    snprintf(mapPath, 128, "./assets/maps/%s.sgm", mapName);

    FILE *file = fopen(mapPath, "r");

    if (file == nullptr) {
        printf("Unable to read map %s.sgm", mapName);

        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = new char[fileSize];
    fread(buffer, 1, fileSize, file);

    if ((buffer[0] == 'S' && buffer[1] == 'G' && buffer[2] == 'M' && buffer[3] == 'V' && buffer[4] == '1') == false) {
        printf("Unable to read map wrong file magic (SGMV1 expected)");

        exit(1);
    }

    unsigned char MapTileBlockSizeByte1 = buffer[5];
    unsigned char MapTileBlockSizeByte2 = buffer[6];
    unsigned char MapTileBlockSizeByte3 = buffer[7];
    unsigned char MapTileBlockSizeByte4 = buffer[8];

    unsigned long mapTileBlockSize = (MapTileBlockSizeByte1 << 24) | (MapTileBlockSizeByte2 << 16) | (MapTileBlockSizeByte3 << 8) | MapTileBlockSizeByte4;
    unsigned long textureTableBlockSize = (buffer[mapTileBlockSize + 9] << 24) | (buffer[mapTileBlockSize + 10] << 16) | (buffer[mapTileBlockSize + 11] << 8) | buffer[mapTileBlockSize + 12];

    layout.push_back({});

    /**
     * Load map tiles
     */
    for (long i = 9; i < mapTileBlockSize; i += 10) {
        signed short tileType;
        unsigned short wallTextureId, floorTextureId, ceilingTextureId;
        unsigned short wallThickness;

        if (bigEndian == false) {
            swapEndianness(&buffer[i], 2); // tileType
            swapEndianness(&buffer[i + 2], 2); // wallTextureId
            swapEndianness(&buffer[i + 4], 2); // floorTextureId
            swapEndianness(&buffer[i + 6], 2); // ceilingTextureId
            swapEndianness(&buffer[i + 8], 2); // getThickness
        }

        memcpy(&tileType, buffer + i, 2);
        memcpy(&wallTextureId, buffer + i + 2, 2);
        memcpy(&floorTextureId, buffer + i + 4, 2);
        memcpy(&ceilingTextureId, buffer + i + 6, 2);
        memcpy(&wallThickness, buffer + i + 8, 2);

        if (tileType == 0) {
            row++;

            layout.push_back({});

            continue;
        }

        MapTile mapTile = MapTile(
            tileType,
            wallTextureId,
            floorTextureId,
            ceilingTextureId,
            (float)wallThickness / 100
        );

        layout[row].push_back(mapTile);
    }


    /**
     * Load map textures
     */
    textures->reset();

    int textureId = 0;

    for (long i = mapTileBlockSize + 13; i < mapTileBlockSize + textureTableBlockSize + 13;) {
        int textureFilenameLength = (buffer[i] << 8) | buffer[i + 1];
        char textureFilename[textureFilenameLength];

        i += 2;

        for (short b = 0; b < textureFilenameLength; b++) {
            textureFilename[b] = buffer[i + b];
        }
        textureFilename[textureFilenameLength] = 0x00;

        i += textureFilenameLength;

        textures->loadTexture(textureId, textureFilename);

        textureId++;
    }

    delete buffer;

    fclose(file);
}

void Map::swapEndianness(char* data, size_t size)
{
    for (size_t i = 0; i < size / 2; i++) {
        char buffer = data[i];

        data[i] = data[size - i - 1];
        data[size - i - 1] = buffer;
    }
}
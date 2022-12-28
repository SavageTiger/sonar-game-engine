#include <cstdlib>
#include <GL/gl.h>
#include <cstdio>
#include "Map.h"
#include "Textures.h"

void Map::renderWall(int row, int column, Textures* textures) {
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
}

bool Map::isWall(int x, int y, short margin)
{
    int column = x / TILE_SIZE;
    int row = y / TILE_SIZE;

    if (row < 0 || column < 0) {
        return false;
    }

    if (row >= layout.size()) {
        return false;
    }

    if (column >= layout[row].size()) {
        return false;
    }

    if (margin > 0 && (
        isWall(x - margin, y - margin) ||
        isWall(x + margin, y - margin) ||
        isWall(x - margin, y + margin) ||
        isWall(x + margin, y + margin))
    ) {
        return true;
    }

    return layout[row][column] == 49 || layout[row][column] == 50;
}

float Map::wallThickness(int x, int y)
{
    int column = x / TILE_SIZE;
    int row = y / TILE_SIZE;

    return layout[row][column] == 50 ? 0.5 : 1;
}

int Map::getTextureId(float x, float y)
{
    int column = x / TILE_SIZE;
    int row = y / TILE_SIZE;

    return layout[row][column] == 49 ? 0 : 1;
}

void Map::loadMap(const char* mapName) {
    int fileChar;
    char mapPath[128] = {0};

    int row = 0;
    int column = 0;

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
            layout[row].push_back(fileChar);

            column++;
        }

        if (fileChar == 10) {
            column = 0;

            row++;
        }
    } while (fileChar != EOF);
}


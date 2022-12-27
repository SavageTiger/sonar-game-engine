#include <cstdlib>
#include <GL/gl.h>
#include <cstdio>
#include "map.h"
#include "textures.h"

void map::renderWall(int row, int column, textures* textures) {
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

void map::renderFloor(int row, int column, textures* textures) {
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

void map::renderMap(const char* mapName, textures* textures) {
    if (mapLoaded == false) {
        map::loadMap(mapName);

        mapLoaded = true;
    }

    for (int r = 0; r < layout.size(); r++) {
        for (int c = 0; c < layout[r].size(); c++) {
            switch (layout[r][c]) {
                case 48:
                    map::renderFloor(r, c, textures);
                    break;

                case 49:
                    map::renderWall(r, c, textures);
                    break;
            }
        }
    }
}

bool map::isWall(int x, int y, short margin)
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

float map::wallThickness(int x, int y)
{
    int column = x / TILE_SIZE;
    int row = y / TILE_SIZE;

    return layout[row][column] == 50 ? 0.5 : 1;
}

int map::getTextureId(float x, float y)
{
    int column = x / TILE_SIZE;
    int row = y / TILE_SIZE;

    return layout[row][column] == 49 ? 0 : 1;
}

void map::loadMap(const char* mapName) {
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

        if (fileChar == 49 || fileChar == 48) {
            layout[row].push_back(fileChar);

            column++;
        }

        if (fileChar == 10) {
            column = 0;

            row++;
        }
    } while (fileChar != EOF);
}


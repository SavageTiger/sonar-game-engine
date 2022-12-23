#include <GL/gl.h>
#include <SOIL/SOIL.h>
#include "textures.h"
#include <cstdio>

void textures::loadTexture(int textureId)
{
    this->loadTextureFromDisk(textureId);

    // TODO: REMOVE ME; no longer required when the debug map is gone.
    glColor4f(1,1,1,0);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        64,
        64,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        textureMemory[textureId]
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

int textures::getTextureRFromXandY(int textureId, int x, int y)
{
    this->loadTextureFromDisk(textureId);

    return textureMemory[textureId][(y * textureHeight[textureId] + x) * 3 + 0];
}

int textures::getTextureGFromXandY(int textureId, int x, int y)
{
    this->loadTextureFromDisk(textureId);

    return textureMemory[textureId][(y * textureHeight[textureId] + x) * 3 + 1];
}

int textures::getTextureBFromXandY(int textureId, int x, int y)
{
    this->loadTextureFromDisk(textureId);

    return textureMemory[textureId][(y * textureHeight[textureId] + x) * 3 + 2];
}

int textures::getTextureHeight(int textureId)
{
    this->loadTextureFromDisk(textureId);

    return textureHeight[textureId];
}

int textures::getTextureWidth(int textureId)
{
    this->loadTextureFromDisk(textureId);

    return textureWidth[textureId];
}

void textures::loadTextureFromDisk(int textureId)
{
    if (textureMemory[textureId] == nullptr) {
        char* textures [4] = {
            "maps/box.png",
            "maps/ceiling.png",
            "maps/floor.png",
            "sprites/gun.png"
        };

        textureMemory[textureId] = SOIL_load_image(
            textures[textureId],
            &textureHeight[textureId],
            &textureWidth[textureId],
            0,
            SOIL_LOAD_RGB
        );
    }
}
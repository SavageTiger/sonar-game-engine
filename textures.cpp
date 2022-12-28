#include "textures.h"
#include <cstdio>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

void textures::loadTexture(short textureId)
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
        textureMemory[textureId]->pixels
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

int textures::getTextureRFromXandY(short textureId, short x, short y)
{
    return this->getTextureValueFromXandY(textureId, x, y, 0);
}

int textures::getTextureGFromXandY(short textureId, short x, short y)
{
    return this->getTextureValueFromXandY(textureId, x, y, 1);
}

int textures::getTextureBFromXandY(short textureId, short x, short y)
{
    return this->getTextureValueFromXandY(textureId, x, y, 2);
}

int textures::getTextureHeight(short textureId)
{
    this->loadTextureFromDisk(textureId);

    return textureHeight[textureId];
}

int textures::getTextureWidth(short textureId)
{
    this->loadTextureFromDisk(textureId);

    return textureWidth[textureId];
}

int textures::getTextureValueFromXandY(short textureId, short x, short y, short channel)
{
    this->loadTextureFromDisk(textureId);

    Uint8* pixels = (Uint8*)textureMemory[textureId]->pixels;

    return pixels[(y * textureHeight[textureId] + x) * 3 + channel];
}

void textures::loadTextureFromDisk(short textureId)
{
    if (textureMemory[textureId] == nullptr) {
        char* textures [5] = {
            "maps/box.png",
            "maps/floor.png",
            "maps/ceiling.png",
            "sprites/gun.png",
            "maps/door.png",
        };

        SDL_Surface* originalSurface = IMG_Load(textures[textureId]);

        if (originalSurface == nullptr) {
            printf("Unable to load textures '%s'", textures[textureId]);
        }

        SDL_Surface *normalizedSurface = SDL_ConvertSurfaceFormat(originalSurface, SDL_PIXELFORMAT_RGB24, 0);

        SDL_PixelFormat* pixelFormat = normalizedSurface->format;
        pixelFormat->BytesPerPixel = 3;
        SDL_Surface *rgbSurface = SDL_ConvertSurface(normalizedSurface, pixelFormat, 0);

        textureMemory[textureId] = rgbSurface;
        textureWidth[textureId] = rgbSurface->w;
        textureHeight[textureId] = rgbSurface->h;

        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(normalizedSurface);
    }
}
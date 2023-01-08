#include "Textures.h"
#include <cstdio>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

void Textures::prepTexture(short textureId)
{
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

short Textures::getTextureRFromXandY(short textureId, short x, short y)
{
    return this->getTextureValueFromXandY(textureId, x, y, 0);
}

short Textures::getTextureGFromXandY(short textureId, short x, short y)
{
    return this->getTextureValueFromXandY(textureId, x, y, 1);
}

short Textures::getTextureBFromXandY(short textureId, short x, short y)
{
    return this->getTextureValueFromXandY(textureId, x, y, 2);
}

int Textures::getTextureHeight(short textureId)
{
    return textureHeight[textureId];
}

int Textures::getTextureWidth(short textureId)
{
    return textureWidth[textureId];
}

short Textures::getTextureValueFromXandY(short textureId, short x, short y, short channel)
{
    Uint8* pixel = (Uint8*)textureMemory[textureId]->pixels + y * textureMemory[textureId]->pitch + x * 3;

    return pixel[channel];
}

void Textures::reset() {
    for (auto& texture : textureMemory) {
        delete texture;

        texture = nullptr;
    }

}

void Textures::loadTexture(short textureId, char* filename)
{
    printf("%i", textureId);

    if (textureMemory[textureId] == nullptr) {
        char filenameWithPath[strlen(filename) + strlen("assets/")];

        sprintf(filenameWithPath, "%s/%s", "assets/", filename);

        SDL_Surface* originalSurface = IMG_Load(filenameWithPath);

        if (originalSurface == nullptr) {
            printf("Unable to load textures '%s'", filenameWithPath);

            exit(1);
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


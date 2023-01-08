#include "SDL.h"
#include "SDL_image.h"

#ifndef TEXTURES_H
#define TEXTURES_H

class Textures {
private:
    SDL_Surface* textureMemory[1024];
    short getTextureValueFromXandY(short textureId, short x, short y, short channel);

    int textureHeight[64];
    int textureWidth[64];

public:
    void reset();
    void loadTexture(short textureId, char* filename);

    // TODO: Remove this when debugging is removed
    void prepTexture(short textureId);

    short getTextureRFromXandY(short textureId, short x, short y);
    short getTextureGFromXandY(short textureId, short x, short y);
    short getTextureBFromXandY(short textureId, short x, short y);

    int getTextureHeight(short textureId);
    int getTextureWidth(short textureId);
};


#endif

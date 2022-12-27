
#ifndef TEXTURES_H
#define TEXTURES_H

class textures {
private:
    unsigned char* textureMemory[64];
    void loadTextureFromDisk(short textureId);

    int textureHeight[64];
    int textureWidth[64];

public:
    void loadTexture(short textureId);

    int getTextureRFromXandY(short textureId, short x, short y);
    int getTextureGFromXandY(short textureId, short x, short y);
    int getTextureBFromXandY(short textureId, short x, short y);

    int getTextureHeight(short textureId);
    int getTextureWidth(short textureId);
};


#endif


#ifndef TEXTURES_H
#define TEXTURES_H

class textures {
private:
    unsigned char* textureMemory[64];
    void loadTextureFromDisk(int textureId);

    int textureHeight[64];
    int textureWidth[64];

public:
    void loadTexture(int textureId);

    int getTextureRFromXandY(int textureId, int x, int y);
    int getTextureGFromXandY(int textureId, int x, int y);
    int getTextureBFromXandY(int textureId, int x, int y);

    int getTextureHeight(int textureId);
    int getTextureWidth(int textureId);
};


#endif

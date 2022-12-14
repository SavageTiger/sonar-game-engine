
#ifndef TEXTURES_H
#define TEXTURES_H

class textures {
private:
    unsigned char* textureMemory[64] = {nullptr};
    void loadTextureFromDisk(int textureId);

    int textureHeight = 64;
    int textureWidth = 64;

public:
    void loadTexture(int textureId);
    int getTextureRFromXandY(int textureId, int x, int y);
    int getTextureGFromXandY(int textureId, int x, int y);
    int getTextureBFromXandY(int textureId, int x, int y);
    int getMapRFromXandY(int x, int y);
    int getMapGFromXandY(int x, int y);
    int getMapBFromXandY(int x, int y);
};


#endif

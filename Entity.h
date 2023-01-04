#ifndef SPRITE_H
#define SPRITE_H

#include "Resolution.h"
#include "Player.h"
#include "Wall.h"

class Entity {
private:
    float getRadians(float degrees);

public:
    void render(
        float size,
        int spriteX,
        int spriteY,
        float distanceFromCieling,
        Player *player,
        Textures* textures,
        Resolution* resolution,
        Wall** walls
    );
};


#endif

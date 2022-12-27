#ifndef SPRITE_H
#define SPRITE_H

#include "player.h"
#include "wall.h"



class entity {
private:
    float getRadians(float degrees);

public:
    void render(
        float size,
        int spriteX,
        int spriteY,
        float distanceFromCieling,
        player *player,
        textures* textures,
        wall** walls
    );
};


#endif

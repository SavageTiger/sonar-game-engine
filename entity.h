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
        float spriteX,
        float spriteY,
        float spriteTop,
        player *player,
        textures* textures,
        wall** walls
    );
};


#endif

#ifndef SPRITE_H
#define SPRITE_H

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
        Wall** walls
    );
};


#endif

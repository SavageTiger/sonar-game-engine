#ifndef SPRITE_H
#define SPRITE_H

#include "Entities.h"
#include "Resolution.h"
#include "Player.h"
#include "Wall.h"

class Entity {
private:
    float getRadians(float degrees);

public:
    void render(
        EntityProperties* entity,
        Player *player,
        Textures* textures,
        Resolution* resolution,
        Wall** walls
    );
};


#endif

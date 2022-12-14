#ifndef SPRITE_H
#define SPRITE_H

#include "player.h"

class entity {
private:
    float getRadians(float degrees);

public:
    void render(player *player);
};


#endif

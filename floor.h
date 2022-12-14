#ifndef FLOOR_H
#define FLOOR_H

#include "player.h"
#include "textures.h"
#include "wall.h"

class floor {
public:
    static void render(textures *textures, player *player, wall *wall);
};


#endif
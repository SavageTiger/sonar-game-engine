#ifndef CEILING_H
#define CEILING_H

#include "player.h"
#include "textures.h"
#include "wall.h"

class ceiling {
public:
    static void render(textures *textures, player *player, wall *wall);
};

#endif
#ifndef CEILING_H
#define CEILING_H

#include "Player.h"
#include "Textures.h"
#include "Wall.h"

class Ceiling {
public:
    static void render(Textures *textures, Player *player, Wall *wall, Map* map);
};

#endif
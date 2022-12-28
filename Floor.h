#ifndef FLOOR_H
#define FLOOR_H

#include "Player.h"
#include "Textures.h"
#include "Wall.h"

class Floor {
public:
    static void render(Textures *textures, Player *player, Wall *wall);
};


#endif
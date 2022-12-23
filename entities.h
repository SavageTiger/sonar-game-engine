#ifndef THREEDEE_ENTITIES_H
#define THREEDEE_ENTITIES_H

#include "player.h"
#include "wall.h"
#include "textures.h"

class entities {

public:
    void render(player *player, textures* textures, wall** walls);

};


#endif
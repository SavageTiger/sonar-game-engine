#ifndef THREEDEE_ENTITIES_H
#define THREEDEE_ENTITIES_H

#include "player.h"
#include "wall.h"
#include "textures.h"

struct entityProperties {
    float size;
    int tileTop;
    int tileLeft;
    float distanceFromCieling;
};

class entities {

private:
    entityProperties entityMemory[128];

    void loadEntities(map* map);

public:
    entities(map *map);

    void render(player *player, textures* textures, wall** walls);

};


#endif
#ifndef THREEDEE_ENTITIES_H
#define THREEDEE_ENTITIES_H

#include "Player.h"
#include "Wall.h"
#include "Textures.h"
#include "Resolution.h"

#define ENTITY_TYPE_WEAPON 0;
#define ENTITY_TYPE_ENEMY 1;

struct EntityProperties {
    float size;
    short textureId;
    int tileTop;
    int tileLeft;
    float distanceFromCeiling;
    short type;
};

class Entities {

private:
    EntityProperties entityMemory[128];

    void loadEntities(Map* map);

public:
    Entities(Map *map);

    void render(Player *player, Textures* textures, Wall** walls, Resolution* resolution);

};


#endif
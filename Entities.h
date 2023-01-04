#ifndef THREEDEE_ENTITIES_H
#define THREEDEE_ENTITIES_H

#include "Player.h"
#include "Wall.h"
#include "Textures.h"
#include "Resolution.h"

struct entityProperties {
    float size;
    int tileTop;
    int tileLeft;
    float distanceFromCieling;
};

class Entities {

private:
    entityProperties entityMemory[128];

    void loadEntities(Map* map);

public:
    Entities(Map *map);

    void render(Player *player, Textures* textures, Wall** walls, Resolution* resolution);

};


#endif
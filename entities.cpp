#include "entities.h"
#include "entity.h"

struct entityProperties {
    float size;
    int x;
    int y;
    float top;
};

entity G_ENTITY;

void entities::render(player *player, textures* textures, wall** walls)
{
    entityProperties entities[1];

    entityProperties gun;

    gun.size = .3;
    gun.x = 90;
    gun.y = 90;
    gun.top = .7;

    entities[0] = gun;

    for (int i = 0; i < sizeof(entities); i++) {
        G_ENTITY.render(
            entities[i].size,
            entities[i].x,
            entities[i].y,
            entities[i].top,
            player,
            textures,
            walls
        );
    }
}

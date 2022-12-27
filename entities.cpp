#include "entities.h"
#include "entity.h"

entity G_ENTITY;

entities::entities(map* map) {
    this->loadEntities(map);
}

void entities::render(player *player, textures* textures, wall** walls)
{
    for (auto& entity : entityMemory) {
        if (entity.size == 0) {
            break;
        }

        G_ENTITY.render(
            entity.size,
            (entity.tileLeft * (TILE_SIZE) - (TILE_SIZE / 2)),
            (entity.tileTop * (TILE_SIZE) - (TILE_SIZE / 2)),
            entity.distanceFromCieling,
            player,
            textures,
            walls
        );
    }
}

void entities::loadEntities(map* map) {
    entityProperties gun;

    gun.size = .3;
    gun.tileTop = 5;
    gun.tileLeft = 2;
    gun.distanceFromCieling = .7;

    entityMemory[0] = gun;
}

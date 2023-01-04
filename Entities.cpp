#include "Entities.h"
#include "Entity.h"

Entity G_ENTITY;

Entities::Entities(Map* map) {
    this->loadEntities(map);
}

void Entities::render(Player *player, Textures* textures, Wall** walls, Resolution* resolution)
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
            resolution,
            walls
        );
    }
}

void Entities::loadEntities(Map* map) {
    entityProperties gun;

    gun.size = .7;
    gun.tileTop = 5;
    gun.tileLeft = 2;
    gun.distanceFromCieling = 0.3;

    entityMemory[0] = gun;
}

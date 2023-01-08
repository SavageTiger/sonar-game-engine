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
            &entity,
            player,
            textures,
            resolution,
            walls
        );
    }
}

void Entities::loadEntities(Map* map) {
    EntityProperties gun;
    EntityProperties soldier;

    gun.size = .7;
    gun.textureId = 3;
    gun.tileTop = 5;
    gun.tileLeft = 2;
    gun.distanceFromCeiling = 0.3;
    gun.type = ENTITY_TYPE_WEAPON;

    soldier.size = .7;
    soldier.textureId = 3;
    soldier.tileTop = 2;
    soldier.tileLeft = 2;
    soldier.distanceFromCeiling = 0.3;
    soldier.type = ENTITY_TYPE_ENEMY;

    entityMemory[0] = gun;
    entityMemory[1] = soldier;
}

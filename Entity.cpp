#include "Entity.h"
#include "Resolution.h"
#include "math.h"
#include <GL/gl.h>

void Entity::render(
    EntityProperties* entity,
    Player *player,
    Textures* textures,
    Resolution* resolution,
    Wall** walls
) {
    int
        spriteX = (entity->tileLeft * (TILE_SIZE) - (TILE_SIZE / 2)),
        spriteY = (entity->tileTop * (TILE_SIZE) - (TILE_SIZE / 2));

    float spriteDistance = sqrt(pow(*player->getX() - spriteX, 2) + pow(*player->getY() - spriteY, 2));

    spriteX = spriteX - *player->getX(),
    spriteY = spriteY - *player->getY();

    float eyeX, eyeY, objectAngle;

    eyeX = sinf(player->getLookingDirectionInRadians());
    eyeY = cosf(player->getLookingDirectionInRadians());

    objectAngle = atan2f(eyeY, eyeX) - atan2f(spriteX, spriteY);

    if (objectAngle < M_PI) {
        objectAngle += 2 * M_PI;
    }

    if (objectAngle > M_PI) {
        objectAngle -= 2 * M_PI;
    }

    bool objectVisible = (fabs(objectAngle) < getRadians(FOV) / 2) && spriteDistance > 40;

    int spriteHeight = textures->getTextureHeight(3);
    int spriteWidth = textures->getTextureWidth(3);

    if (objectVisible == false) {
        return;
    }

    float screenHeight = resolution->getResolutionHeight() * TILE_SIZE;

    float objectCeiling = (resolution->getResolutionHeight() / 2) - (screenHeight / spriteDistance / 2);
    float objectFloor = objectCeiling + (screenHeight / spriteDistance / 2);

    float objectAspectRatio = ((float)spriteHeight / (float)spriteWidth);

    float objectHeight = (objectFloor - objectCeiling) * entity->size;
    float objectWidth = objectHeight / objectAspectRatio;

    int objectMiddle = (.5 * (objectAngle / (getRadians(FOV) / 2)) + .5) * resolution->getResolutionWidth();

    glPointSize(resolution->getPaintSize() * 2);
    glBegin(GL_POINTS);

    int renderRowOffset = (objectFloor - objectCeiling) * entity->distanceFromCeiling;

    for (int renderColumn = 0; renderColumn < objectWidth; renderColumn++) {
        for (int renderRow = renderRowOffset; renderRow < objectHeight + renderRowOffset; renderRow++) {
            int columnX = objectMiddle + renderColumn - (objectWidth / 2);

            if (columnX <= 0 || columnX >= resolution->getResolutionWidth()) {
                continue;
            }

            if (walls[columnX]->distance < spriteDistance && (spriteDistance - walls[columnX]->distance) > 50) {
                continue;
            }

            short
                textureX = (spriteWidth / objectWidth) * renderColumn,
                textureY = (spriteHeight / objectHeight) * (renderRow - renderRowOffset);

            int
                colorR = textures->getTextureRFromXandY(entity->textureId, textureX, textureY),
                colorG = textures->getTextureGFromXandY(entity->textureId, textureX, textureY),
                colorB = textures->getTextureBFromXandY(entity->textureId, textureX, textureY);

            if (colorR == 255 && colorG == 0 && colorB == 255) {
                continue;
            }

            glColor3ub(colorR, colorG, colorB);

            glVertex2i(columnX, objectCeiling + renderRow);
        }
    }

    glEnd();
}

float Entity::getRadians(float degrees)
{
    return M_PI * degrees / 180;
}

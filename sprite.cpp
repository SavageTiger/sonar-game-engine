#include "entity.h"
#include "resolution.h"
#include "math.h"
#include <cstdio>
#include <GL/gl.h>

float entity::getRadians(float degrees) {

    return M_PI * degrees / 180;

}

void entity::render(player *player) {

    /*
    float spriteDirection = atan2(92 - *player->getY(), 92 - *player->getX());
    float spriteDirectionDegrees = spriteDirection * (180.0 / M_PI);

    if (spriteDirectionDegrees < 0) {
        spriteDirectionDegrees += 360;
    }

    float delta = (*player->getLookingDirection() - (RESOLUTION_WIDTH / 2) - spriteDirectionDegrees);

    float betweenDeltaAndTheta = (-spriteDirection - -getRadians(delta)) / 2;

    float spriteX = (-betweenDeltaAndTheta  * (180.0 / M_PI)) * (RESOLUTION_WIDTH * 4) / RESOLUTION_WIDTH;

    float bla = ((spriteDirection + betweenDeltaAndTheta) * (180.0 / M_PI)); // ;


    printf("%f - %f - %f - %f\r\n", -spriteDirection, -getRadians(delta), betweenDeltaAndTheta, spriteX);


    //int spriteX = blaDegrees * RESOLUTION_WIDTH / RESOLUTION_WIDTH;

    float spriteLookX = (*player->getX() + (500 * cos(getRadians(spriteDirectionDegrees))));
    float spriteLookY = (*player->getY() + (500 * sin(getRadians(spriteDirectionDegrees))));

    float spriteLookX2 = (*player->getX() + (500 * cos(getRadians(delta))));
    float spriteLookY2 = (*player->getY() + (500 * sin(getRadians(delta))));

    float spriteLookX3 = (*player->getX() + (500 * cos(getRadians(bla))));
    float spriteLookY3 = (*player->getY() + (500 * sin(getRadians(bla))));

    glColor3ub(
            255, 0, 255
    );
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(*player->getX(), *player->getY());
    glVertex2i(spriteLookX, spriteLookY);
    glVertex2i(*player->getX(), *player->getY());
    glVertex2i(spriteLookX2, spriteLookY2);

    glColor3ub(
            255, 255, 255
    );
    glVertex2i(*player->getX(), *player->getY());
    glVertex2i(spriteLookX3, spriteLookY3);
    glEnd();

    glPointSize(8);
    glBegin(GL_POINTS);

    glVertex2i((90), (90));

    glVertex2i(515 + spriteX, 100);

/*    float playerAngle = -(player->getLookingDirectionInRadians() - (M_PI * 2));

*/


    float
        spriteX = 90 - *player->getX(),
        spriteY = 90 - *player->getY(),
        spriteZ = 20;

    //float nx = spriteX * (cos(player->getLookingDirectionInRadians()) * (180 / M_PI)) - spriteY * (sin(player->getLookingDirectionInRadians()) * (180 / M_PI));
    float ny = spriteX * (sin(player->getLookingDirectionInRadians()) * (180 / M_PI)) + spriteY * (cos(player->getLookingDirectionInRadians()) * (180 / M_PI));

    //spriteX = a;
    //spriteY = b;

    float pa = -(*player->getLookingDirection());

    if (pa < 0) {
        pa += 360;
    }

    float CS=cos(getRadians(pa)), SN=sin(getRadians(pa));

    float a = spriteY * CS + spriteX * SN;
    float b = spriteX * CS - spriteY * SN;

    spriteX = a;
    spriteY = b;

    //spriteX = (spriteX * 90.0/spriteY)+(120/2);
    //spriteY = (spriteZ * 90.0/spriteY)+(80/2);

    glColor3ub(
            255, 0, 255
    );

    float n = (float)(RESOLUTION_WIDTH - (RESOLUTION_WIDTH / 4));
    float n2 = (float)(RESOLUTION_HEIGHT - (RESOLUTION_HEIGHT / 4));

    spriteX = spriteX * n / spriteY + (RESOLUTION_WIDTH / 2);
    spriteY = spriteZ * 80 / spriteY + (80 / 2);

    //printf("%f - %f\r\n", RESOLUTION_WIDTH - (RESOLUTION_WIDTH / 10), spriteY);
    //printf("%f - %f\r\n", spriteX * 8, spriteY * 8);

    //printf("%f - %f - %f - %f - %f\r\n", pa, CS, SN, a, b);
    //printf("%f - %f - %f - %f - %f\r\n", pa, CS, SN, a, b);
    printf("%f\r\n", n2);
    //printf("%f\r\n", spriteX * 108 / spriteY);


    glPointSize(8);
    glBegin(GL_POINTS);

    glColor3ub(
            255, 0, 255
    );

    glVertex2i(spriteX * 2, spriteY * 2);

    //printf("%f\r\n", nx);

    glEnd();
}
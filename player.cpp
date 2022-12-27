#include "player.h"
#include <GL/freeglut.h>
#include <math.h>
#include <cstdio>

#define TwicePI 6.2831853

void player::render() {
    glColor3f(0,1,1.0);

    recalculateLookingDirection();

    // The player
    glColor3f(0,0,1.0);
    glBegin(GL_QUADS);
    glVertex2f(playerX - 2.5, playerY - 2.5);
    glVertex2f(playerX + 2.5, playerY - 2.5);
    glVertex2f(playerX + 2.5, playerY + 2.5);
    glVertex2f(playerX - 2.5, playerY + 2.5);
    glEnd();

    // Looking direction
    glColor3f(1,0,0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(lookingDirectionX, lookingDirectionY);
    glVertex2i(playerX, playerY);
    glEnd();

    return;
}

void player::buttonPressed(int keyCode, bool keyDown)
{
    switch (keyCode) {
        case 100: // Left (100)
            keyPressState.left = keyDown;
            break;
        case 101: // Up (101)
            keyPressState.up = keyDown;
            break;
        case 102: // Right (102)
            keyPressState.right = keyDown;
            break;
        case 103: // Down (103)
            keyPressState.down = keyDown;
            break;
    }
}

bool player::move(map* map)
{
    if (keyPressState.left == true) {
        player::turnLeft();
    }

    if (keyPressState.right == true) {
        player::turnRight();
    }

    if (keyPressState.up == true) {
        player::walk(true, map);
    }

    if (keyPressState.down == true) {
        player::walk(false, map);
    }

    recalculateLookingDirection();

    return keyPressState.left == true ||
           keyPressState.right == true ||
           keyPressState.up == true ||
           keyPressState.down == true;
}

void player::walk(bool forward, map* map)
{
    short collisionMargin = TILE_SIZE / 8;
    float movingDistance = 5;

    float lookingDirectionRadians = getLookingDirectionInRadians();

    short movementDirection = forward ? 1 : -1;

    int
        desiredX = playerX + movementDirection * movingDistance * cos(lookingDirectionRadians),
        desiredY = playerY + movementDirection * movingDistance * sin(lookingDirectionRadians);

    if (map->isWall(desiredX, desiredY, collisionMargin) == true) {
        if (map->isWall(playerX, desiredY, collisionMargin) == false) {
            desiredX = playerX;
        } else if (map->isWall(desiredX, playerY, collisionMargin) == false) {
            desiredY = playerY;
        } else {
            return;
        }
    }

    playerX = desiredX;
    playerY = desiredY;
}

void player::turnRight()
{
    lookingDirection += 3;

    if (lookingDirection > 360) {
        lookingDirection = 0;

        player::turnRight();

        return;
    }
}

void player::turnLeft()
{
    lookingDirection -= 3;

    if (lookingDirection < 0) {
        lookingDirection = 360;

        player::turnLeft();

        return;
    }
}


int* player::getLookingDirection()
{
    return &lookingDirection;
}

float player::getLookingDirectionInRadians()
{
    return *this->getLookingDirection() * M_PI / 180.0;
}

int* player::getX()
{
    return &playerX;
}

int* player::getY()
{
    return &playerY;
}

void player::recalculateLookingDirection()
{
    lookingDirectionX = (playerX + (18 * cos(lookingDirection * TwicePI / 360)));
    lookingDirectionY = (playerY + (18 * sin(lookingDirection * TwicePI / 360)));
}
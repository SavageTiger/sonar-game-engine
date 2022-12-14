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
    int wallCheckX, wallCheckY;

    wallCheckX = calculateMoveX(forward, 15);
    wallCheckY = calculateMoveY(forward, 15);

    if (map->isWall(wallCheckX, wallCheckY) == true) {
        return;
    }

    playerX = calculateMoveX(forward, 5);
    playerY = calculateMoveY(forward, 5);
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


int player::calculateMoveX(bool forward, int desiredDistance)
{
    if (forward == true) {
        return (playerX + (desiredDistance * cos(lookingDirection * TwicePI / 360)));
    }

    return (playerX - (desiredDistance * cos(lookingDirection * TwicePI / 360)));
}

int player::calculateMoveY(bool forward, int desiredDistance)
{
    if (forward == true) {
        return (playerY + (desiredDistance * sin(lookingDirection * TwicePI / 360)));
    }

    return (playerY - (desiredDistance * sin(lookingDirection * TwicePI / 360)));
}


void player::recalculateLookingDirection()
{
    lookingDirectionX = (playerX + (18 * cos(lookingDirection * TwicePI / 360)));
    lookingDirectionY = (playerY + (18 * sin(lookingDirection * TwicePI / 360)));
}
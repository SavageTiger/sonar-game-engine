#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

class player {
private:
    struct keysPressed {
        bool up;
        bool down;
        bool left;
        bool right;
    };

    keysPressed keyPressState;

    int playerX = 150;
    int playerY = 400;

    int lookingDirection  = 270;
    int lookingDirectionX = 0;
    int lookingDirectionY = 0;

    void recalculateLookingDirection();
    void turnRight();
    void turnLeft();
    int calculateMoveX(bool forward, int desiredDistance);
    int calculateMoveY(bool forward, int desiredDistance);
    void walk(bool forward, map* map);

public:
    void render();

    void buttonPressed(int keyCode, bool keyDown);
    bool move(map* map);

    int* getLookingDirection();
    float getLookingDirectionInRadians();
    int* getX();
    int* getY();

};


#endif

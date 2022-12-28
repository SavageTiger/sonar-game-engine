#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"

class Player {
private:
    struct keysPressed {
        bool up;
        bool down;
        bool left;
        bool right;
    };

    keysPressed keyPressState;

    int playerX = 80;
    int playerY = 180;

    int lookingDirection  = 270;
    int lookingDirectionX = 0;
    int lookingDirectionY = 0;

    void recalculateLookingDirection();
    void turnRight();
    void turnLeft();
    void walk(bool forward, Map* map);

public:
    void render();

    void buttonPressed(int keyCode, bool keyDown);
    bool move(Map* map);

    int* getLookingDirection();
    float getLookingDirectionInRadians();
    int* getX();
    int* getY();

};


#endif

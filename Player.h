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
        bool space;
    };

    keysPressed keyPressState;

    int playerX = 151;
    int playerY = 388;

    int lookingDirection  = 78;

    void turnRight();
    void turnLeft();
    void walk(bool forward, Map* map);

public:
    void render();

    void buttonPressed(int keyCode, bool keyDown);
    bool move(Map* map);
    bool interact(Map* map);

    int* getLookingDirection();
    float getLookingDirectionInRadians();
    int* getX();
    int* getY();

};


#endif

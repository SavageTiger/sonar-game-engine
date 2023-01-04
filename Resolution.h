#ifndef RESOLUTION_H
#define RESOLUTION_H

#define FOV 70

#define MAX_RESOLUTION_WIDTH 640;
#define MAX_RESOLUTION_HEIGHT 640;

class Resolution {
private:
    int previousAverageFPS = 0;

    float paintSize = 2;
    short resolutionWidth = MAX_RESOLUTION_WIDTH;
    short resolutionHeight = MAX_RESOLUTION_HEIGHT;

public:
    void autoScale(short targetFPS, short averageFPS);


    short getResolutionWidth();
    short getResolutionHeight();
    float getPaintSize();
};

#endif

#include "Resolution.h"
#include <cstdio>

void Resolution::autoScale(short targetFPS, short averageFPS)
{
    if (averageFPS == previousAverageFPS) {
        return;
    }

    resolutionHeight = MAX_RESOLUTION_HEIGHT;
    resolutionWidth = MAX_RESOLUTION_WIDTH;

    if (averageFPS >= targetFPS) {
        return;
    }

    int originalResolution = MAX_RESOLUTION_HEIGHT;

    int percentage = ((float)averageFPS / (float)targetFPS) * 100;

    printf("%i\r\n", percentage);

    resolutionHeight = originalResolution / 100 * percentage;
    resolutionWidth = originalResolution / 100 * percentage;

    float deltaHeight =  (float)originalResolution / (float)resolutionHeight;

    paintSize = 1.5 * deltaHeight;

    previousAverageFPS = averageFPS;
}

short Resolution::getResolutionWidth()
{
    return resolutionWidth;
}

short Resolution::getResolutionHeight()
{
    return resolutionHeight;
}

float Resolution::getPaintSize()
{
    return paintSize;
}

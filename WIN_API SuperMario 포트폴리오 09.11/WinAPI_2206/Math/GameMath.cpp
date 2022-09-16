#include "Framework.h"

int GameMath::Random(const int & min, const int & max)
{
    return rand() % (max - min) + min;
}

UINT GameMath::Random(const UINT & min, const UINT & max)
{
    return rand() % (max - min) + min;
}

float GameMath::Random(const float & min, const float & max)
{
    float normal = rand() / (float)RAND_MAX;

    return (max - min) * normal + min;
}

float GameMath::Clamp(const float & min, const float & max, const float & value)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

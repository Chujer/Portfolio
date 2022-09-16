#pragma once

namespace GameMath
{
    enum class Direction
    {
        LEFT, RIGHT, UP, DOWN, NONE
    };

    int Random(const int& min, const int& max);
    UINT Random(const UINT & min, const UINT & max);
    float Random(const float& min, const float& max);

    float Clamp(const float& min, const float& max, const float& value);
};
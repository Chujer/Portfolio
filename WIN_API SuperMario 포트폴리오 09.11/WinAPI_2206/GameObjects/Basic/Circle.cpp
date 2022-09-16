#include "Framework.h"

Circle::Circle()
{
}

Circle::Circle(Vector2 pos, float radius)
    : pos(pos), radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::Render(HDC hdc)
{
    if (!isActive) return;

    Ellipse(hdc,
        (int)(pos.x - radius),
       (int)(pos.y - radius),
       (int)(pos.x + radius),
       (int)(pos.y + radius)
    );
}


bool Circle::IsCollision(Vector2 pos)
{
    if (!isActive) return false;

    float x = pos.x - this->pos.x;
    float y = pos.y - this->pos.y;

    float distance = sqrtf(x * x + y * y);    

    return distance < radius;
}

bool Circle::IsCollision(Circle * circle)
{
    if (!isActive) return false;

    float x = pos.x - circle->pos.x;
    float y = pos.y - circle->pos.y;

    float distance = sqrtf(x * x + y * y);

    return distance < radius + circle->radius;
}

bool Circle::IsCollision(Rect * rect)
{
    return rect->IsCollision(this);
}

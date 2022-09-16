#pragma once

class Circle
{
public:
    Circle();
    Circle(Vector2 pos, float radius);
    ~Circle();

    void Render(HDC hdc);

    bool IsCollision(Vector2 pos);
    bool IsCollision(Circle * circle);
    bool IsCollision(class Rect * rect);

    Vector2 & Pos() { return pos; }
    bool & Active() { return isActive; }

    float Radius() { return radius; }

protected:
    bool isActive = true;

    Vector2 pos;
    float radius = 0.0f;
};
#pragma once

class Rect
{
public:
    Rect();
    Rect(Vector2 pos, Vector2 size);
    Rect(float left, float top, float right, float bottom);

    bool IsCollision(const Vector2& point);
    bool IsCollision(const Rect * rect);
    bool IsCollision(IN const Rect * rect, OUT Vector2 & overlapSize);
    bool IsCollision(Circle * circle);

    void Render(HDC hdc);
    void LineRender(HDC hdc);

    void SetRect(float left, float top, float right, float bottom);

    float Left() const { return pos.x - size.x * 0.5f; }
    float Right() const { return pos.x + size.x * 0.5f; }
    float Top() const { return pos.y - size.y * 0.5f; }
    float Bottom() const { return pos.y + size.y * 0.5f; }

    Vector2 Half() const { return size * 0.5f; }

    Vector2 & Pos() { return pos; }
    Vector2 & Size() { return size; }
    bool & Active() { return isActive; }

protected:
    bool isActive = true;

    Vector2 pos;
    Vector2 size;      

};
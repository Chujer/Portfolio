#include "Framework.h"

Rect::Rect()
{
}

Rect::Rect(Vector2 pos, Vector2 size)
    : pos(pos), size(size)
{
}

Rect::Rect(float left, float top, float right, float bottom)
{
    SetRect(left, top, right, bottom);
}

bool Rect::IsCollision(const Vector2 & point)
{
    if (!isActive) return false;

    if (point.x > Left() && point.x < Right())
    {
        if (point.y > Top() && point.y < Bottom())
            return true;
    }

    return false;
}

bool Rect::IsCollision(const Rect * rect)
{
    if (!isActive) return false;
    if (!rect->isActive) return false;

    if (rect->Left() < Right() && rect->Right() > Left())
    {
        if (rect->Top() < Bottom() && rect->Bottom() > Top())
            return true;
    }

    return false;
}

bool Rect::IsCollision(IN const Rect * rect, OUT Vector2 & overlapSize)
{
    if (!isActive) return false;
    if (!rect->isActive) return false;

    float left = max(rect->Left(), Left());
    float right = min(rect->Right(), Right());

    float top = max(rect->Top(), Top());
    float bottom = min(rect->Bottom(), Bottom());

    overlapSize.x = right - left;
    overlapSize.y = bottom - top;

    if (overlapSize.x > 0 && overlapSize.y > 0)
        return true;

    return false;
}

bool Rect::IsCollision(Circle * circle)
{
    if (!isActive) return false;
    if (!circle->Active()) return false;

    //십자가 범위
    if (circle->Pos().x > Left() && circle->Pos().x < Right() ||
        circle->Pos().y > Top() && circle->Pos().y < Bottom())
    {
        Vector2 size(circle->Radius() * 2, circle->Radius() * 2);
        Rect temp(circle->Pos(), size);

        if (IsCollision(&temp))
            return true;
        else
            return false;
    }

    //대각선 범위
    Vector2 edges[4];
    edges[0] = { Left(), Top() };
    edges[1] = { Left(), Bottom() };
    edges[2] = { Right(), Top() };
    edges[3] = { Right(), Bottom() };

    for (Vector2 edge : edges)
    {
        if (circle->IsCollision(edge))
            return true;
    }

    return false;
}

void Rect::Render(HDC hdc)
{
    if (!isActive) return;

    Rectangle(hdc, (int)Left(), (int)Top(), (int)Right(), (int)Bottom());
}

void Rect::LineRender(HDC hdc)
{
    if (!isActive) return;

    MoveToEx(hdc, (int)Left(), (int)Top(), nullptr);
    LineTo(hdc, (int)Left(), (int)Bottom());

    MoveToEx(hdc, (int)Left(), (int)Bottom(), nullptr);
    LineTo(hdc, (int)Right(), (int)Bottom());

    MoveToEx(hdc, (int)Right(), (int)Top(), nullptr);
    LineTo(hdc, (int)Right(), (int)Bottom());

    MoveToEx(hdc, (int)Right(), (int)Top(), nullptr);
    LineTo(hdc, (int)Left(), (int)Top());
}

void Rect::SetRect(float left, float top, float right, float bottom)
{
    pos.x = (left + right) * 0.5f;
    pos.y = (top + bottom) * 0.5f;

    size.x = abs(right - left);
    size.y = abs(bottom - top);
}

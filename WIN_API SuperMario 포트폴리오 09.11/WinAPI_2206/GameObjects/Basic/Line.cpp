#include "Framework.h"

Line::Line()
{
}

Line::Line(Vector2 start, Vector2 end)
    : start(start), end(end)
{
}

Line::~Line()
{
}

void Line::Render(HDC hdc)
{
    MoveToEx(hdc, start.x, start.y, nullptr);
    LineTo(hdc, end.x, end.y);
}

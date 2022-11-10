#pragma once

class Line
{
public:
    Line();
    Line(Vector2 start, Vector2 end);
    ~Line();

    void Render(HDC hdc);

    Vector2 & Start() { return start; }
    Vector2 & End() { return end; }

private:
    Vector2 start;
    Vector2 end;
};
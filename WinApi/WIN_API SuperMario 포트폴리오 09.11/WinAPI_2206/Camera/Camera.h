#pragma once

class Rect;

class Camera : public Singleton<Camera>
{
public:
    Camera();
    ~Camera();

    void Update();

    Vector2 GetPos();
    void SetMapRect(Rect * rect) { mapRect = rect; }
    void SetTarget(Rect * rect) { target = rect; }
    void SetOffset(float x, float y) { offset = { x, y }; }

private:
    void FreeMode();
    void FollowMode();

    void FixPos(Vector2& pos);

private:
    Rect * rect;
    float moveSpeed = 500.0f;
    float followSpeed = 5.0f;

    Rect * mapRect = nullptr;
    Rect * target = nullptr;

    Vector2 offset = Vector2(CENTER_X, CENTER_Y);
    Vector2 destPos;
    
    Vector2 firstPos;
    Vector2 movedPos = { 0,0 };
};
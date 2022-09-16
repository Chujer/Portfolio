#include "Framework.h"

Camera::Camera()
{
    rect = new Rect(Vector2(0, 0), Vector2(WIN_WIDTH, WIN_HEIGHT));
}

Camera::~Camera()
{
    delete rect;
}

void Camera::Update()
{
    if (target == nullptr)
        FreeMode();
    else
        FollowMode();
}

Vector2 Camera::GetPos()
{
    return rect->Pos();
}

void Camera::FreeMode()
{
    if (KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS('A'))
        {
            rect->Pos().x -= moveSpeed * DELTA;            
        }
        if (KEY_PRESS('D'))
        {
            rect->Pos().x += moveSpeed * DELTA;            
        }
       /* if (KEY_PRESS('W'))
        {
            rect->Pos().y -= moveSpeed * DELTA;            
        }
        if (KEY_PRESS('S'))
        {
            rect->Pos().y += moveSpeed * DELTA;            
        }*/

        FixPos(rect->Pos());
    }
}

void Camera::FollowMode()
{
    destPos = target->Pos() - offset;

    FixPos(destPos);

   rect->Pos() = LERP(rect->Pos(), destPos, followSpeed * DELTA);
}

void Camera::FixPos(Vector2 & pos)
{
    if (pos.x < mapRect->Left())
        pos.x = mapRect->Left();

    if (pos.x + rect->Size().x > mapRect->Right())
        pos.x = mapRect->Right() - rect->Size().x;

    if (pos.y < mapRect->Top())
        pos.y = mapRect->Top();

    if (pos.y + rect->Size().y > mapRect->Bottom())
        pos.y = mapRect->Bottom() - rect->Size().y;
}

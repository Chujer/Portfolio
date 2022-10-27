#include "Framework.h"

Move::Move(Transform* target, Vector2* curFrame)
	:target(target), curFrame(curFrame)
{
	endPos = target->Position();
}

Move::~Move()
{
}


void Move::Update()
{
	MoveTarget();
	Animaion();

	target->Position() = SLERP(target->Position(), endPos, 100.0f * DELTA);

}

void Move::MoveTarget()
{
	if (isMove == false)
	{
		if (KEY_DOWN(VK_RIGHT))
		{
			endPos = { target->Position().x + MOVE_POWER,target->Position().y };

			if (curFrame != nullptr)
			{
				curFrame->x = 1;
				curFrame->y = 0;
			}
			isMove = true;
		}
		if (KEY_DOWN(VK_LEFT))
		{
			endPos = { target->Position().x - MOVE_POWER,target->Position().y };
			if (curFrame != nullptr)
			{
				curFrame->x = 5;
				curFrame->y = 0;
			}
			isMove = true;
		}
		if (KEY_DOWN(VK_UP))
		{
			endPos = { target->Position().x ,target->Position().y + MOVE_POWER };
			if (curFrame != nullptr)
			{
				curFrame->x = 3;
				curFrame->y = 0;
			}
			isMove = true;
		}
		if (KEY_DOWN(VK_DOWN))
		{
			endPos = { target->Position().x ,target->Position().y - MOVE_POWER };
			if (curFrame != nullptr)
			{
				curFrame->x = 7;
				curFrame->y = 0;
			}
			isMove = true;
		}

		if (BabaMapManager::Get()->GetPositionTile(endPos) != nullptr && BabaMapManager::Get()->GetPositionTile(endPos)->effect == "STOP" )
			endPos = target->Position();

		if(endPos.x > BabaMapManager::Get()->Right() ||
			endPos.x < BabaMapManager::Get()->Left() ||
			endPos.y > BabaMapManager::Get()->Top() ||
			endPos.y < BabaMapManager::Get()->Bottom() )
			endPos = target->Position();
	}

	if ((target->Position() - endPos).Length() < 0.5f)
	{
		target->Position() = endPos;
		isMove = false;
	}


}

void Move::Animaion()
{
	if (curFrame == nullptr)return;

	if ((int)curFrame->x % 2 == 1)
	{
		if (curFrame->y == 2)
		{
			curFrame->x -= 1;
		}
	}
}

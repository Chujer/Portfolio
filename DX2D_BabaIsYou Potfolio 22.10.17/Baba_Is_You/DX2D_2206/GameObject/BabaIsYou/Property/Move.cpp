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
	Animaion();

	target->Position() = SLERP(target->Position(),  endPos, 100.0f * DELTA);

	for (int i = 0; i < pushTargets.size(); i++)
	{
		pushTargets[i]->Position() = SLERP(pushTargets[i]->Position(), endPos + (nextPos * (i + 1)), 100 * DELTA);
	}
	MoveTarget();
}

void Move::MoveTarget()
{
	if (isMove == false)
	{
		if (KEY_DOWN(VK_RIGHT))
		{
			endPos = { target->Position().x + MOVE_POWER,target->Position().y };
			nextPos = { MOVE_POWER, 0 };
			if (curFrame != nullptr)
			{
				curFrame->x = 1;
				curFrame->y = 0;
			}
			isMove = true;
			pushTargets.clear();
			SetPushObject(endPos);
		}
		if (KEY_DOWN(VK_LEFT))
		{
			endPos = { target->Position().x - MOVE_POWER,target->Position().y };
			nextPos = { -MOVE_POWER, 0 };
			if (curFrame != nullptr)
			{
				curFrame->x = 5;
				curFrame->y = 0;
			}
			isMove = true;
			pushTargets.clear();
			SetPushObject(endPos);
		}
		if (KEY_DOWN(VK_UP))
		{
			endPos = { target->Position().x ,target->Position().y + MOVE_POWER };
			nextPos = { 0, MOVE_POWER };
			if (curFrame != nullptr)
			{
				curFrame->x = 3;
				curFrame->y = 0;
			}
			isMove = true;
			pushTargets.clear();
			SetPushObject(endPos);
		}
		if (KEY_DOWN(VK_DOWN))
		{
			endPos = { target->Position().x ,target->Position().y - MOVE_POWER };
			nextPos = { 0, -MOVE_POWER };
			if (curFrame != nullptr)
			{
				curFrame->x = 7;
				curFrame->y = 0;
			}
			isMove = true;
			pushTargets.clear();
			SetPushObject(endPos);
		}
		SetStop();
	}

	SetFinishMove();

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

void Move::SetStop()
{
	if (pushTargets.size() > 0)
	{
		if (BabaMapManager::Get()->GetPositionAndEffectTile(pushTargets.back()->Position()+nextPos, "STOP") != nullptr)
		{
			endPos = target->Position();
			pushTargets.clear();
			return;
		}

		if ((pushTargets.back()->Position() + nextPos).x > BabaMapManager::Get()->Right() ||
			(pushTargets.back()->Position() + nextPos).x < BabaMapManager::Get()->Left() ||
			(pushTargets.back()->Position() + nextPos).y > BabaMapManager::Get()->Top() ||
			(pushTargets.back()->Position() + nextPos).y < BabaMapManager::Get()->Bottom())
		{
			/*endPos = target->Position();
			pushTargets.clear();
			return;*/
		}
	}

	if (BabaMapManager::Get()->GetPositionAndEffectTile(endPos, "STOP") != nullptr)
		endPos = target->Position();

	if (endPos.x > BabaMapManager::Get()->Right() ||
		endPos.x < BabaMapManager::Get()->Left() ||
		endPos.y > BabaMapManager::Get()->Top() ||
		endPos.y < BabaMapManager::Get()->Bottom())
		endPos = target->Position();
}

void Move::SetPushObject(Vector2 nextPos)
{
	Object* temp = BabaMapManager::Get()->GetPositionTile(nextPos);

	if (BabaMapManager::Get()->GetPositionAndEffectTile(nextPos,"PUSH") == nullptr || BabaMapManager::Get()->GetPositionAndEffectTile(nextPos, "PUSH")->effect != "PUSH")
	{
		return;
	}

	pushTargets.push_back(BabaMapManager::Get()->GetPositionAndEffectTile(nextPos,"PUSH"));
	SetPushObject(nextPos + this->nextPos);
}

void Move::SetFinishMove()
{
	if ((target->Position() - endPos).Length() < 0.5f && isMove == true)
	{
		target->Position() = endPos;
		for (int i = 0; i < pushTargets.size(); i++)
		{
			pushTargets[i]->Position() = endPos + (nextPos * (i + 1));
		}

		isMove = false;
		EventManager::Get()->PlayEvent("CheckIs");
	}
}

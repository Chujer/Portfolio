#include "Framework.h"

Move::Move(Transform* target, Vector2* curFrame)
	:target(target), curFrame(curFrame)
{
	endPos = target->Position();
	particles.resize(5);
	for (int i = 0; i < 5; i++)
	{
		particles[i] = new Particle("Particle/MoveParticle.fx");
		particles[i]->SetRotate(true);
		//ParticleManager::Get()->AddParticle(particles[i]);
	}

	GetColor();
}

Move::~Move()
{
	//for (int i = 0; i < 5; i++)
	//{
	//	ParticleManager::Get()->RemoveParticle(particles[i]);
	//}
}


void Move::Update()
{
	//if (!isMove) return;
	Animaion();

	if (isMove)
	{
		target->Position() = SLERP(target->Position(), endPos, 100.0f * DELTA);

		for (int i = 0; i < pushTargets.size(); i++)
		{
			pushTargets[i]->Position() = SLERP(pushTargets[i]->Position(), endPos + (nextPos * (i + 1)), 100 * DELTA);//  LERP(pushTargets[i]->Position(), endPos + (nextPos * (i + 1)), 100 * DELTA);
		}
	}
	MoveTarget();

	for (Particle* particle : particles)
	{
		particle->Update();
	}
}

void Move::MoveTarget()
{
	if (isMove == false)
	{
		if (KEY_DOWN(VK_RIGHT))
		{
			GetBackObject::Get()->SetPrevData(BabaMapManager::Get()->GetPositionMyself(target));
			ParticlePlay(target->GlobalPosition());
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
			GetBackObject::Get()->SetPrevData(BabaMapManager::Get()->GetPositionMyself(target));
			ParticlePlay(target->GlobalPosition());
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
			GetBackObject::Get()->SetPrevData(BabaMapManager::Get()->GetPositionMyself(target));
			ParticlePlay(target->GlobalPosition());
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
			GetBackObject::Get()->SetPrevData(BabaMapManager::Get()->GetPositionMyself(target));
			ParticlePlay(target->GlobalPosition());
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
	if (isMove) return;

	if ((int)curFrame->x % 2 == 1)
	{
		if (curFrame->y == 2)
		{
			curFrame->x -= 1;
		}
	}
}

//void Move::Render()
//{
//	ParticleManager::Get()->Render();
//}

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

	GetBackObject::Get()->SetPrevData(BabaMapManager::Get()->GetPositionAndEffectTile(nextPos, "PUSH"));
	pushTargets.push_back(BabaMapManager::Get()->GetPositionAndEffectTile(nextPos,"PUSH"));
	SetPushObject(nextPos + this->nextPos);
}

void Move::SetFinishMove()
{
	if ((target->Position() - endPos).Length() < 0.5f && isMove == true)
	{
		target->Position() = endPos; 
		GetBackObject::Get()->SetNextData(BabaMapManager::Get()->GetPositionMyself(target));
		for (int i = 0; i < pushTargets.size(); i++)
		{
			pushTargets[i]->Position() = endPos + (nextPos * (i + 1));
			GetBackObject::Get()->SetNextData(BabaMapManager::Get()->GetPositionAndEffectTile(pushTargets[i]->Position(), "PUSH"));
		}

		isMove = false;

		EventManager::Get()->PlayEvent("CheckIs");
	}
}

void Move::ParticlePlay(Vector2 pos)
{
	for (Particle* particle : particles)
	{
		if (!particle->GetIsPlay())
		{
			particle->Play(pos - Vector2(0,10));
			return;
		}
	}
}

void Move::GetColor()
{
	string temp = BabaMapManager::Get()->GetPositionMyself(target)->tag;
	wstring path = ObjectSample::Get()->GetInstanceData(temp).path;
	Float4 color = Texture::Add(path)->GetCenterPixels();
	for (Particle* particle : particles)
	{
		particle->SetCustomColor(color);
	}
}

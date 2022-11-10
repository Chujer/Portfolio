#include "Framework.h"

Goomba::Goomba()
{
}

Goomba::~Goomba()
{
	for (pair<ActionType,Animation*> animation : animations)
		delete animation.second;

}

void Goomba::Update()
{
	if (!isActive) return;


	//ImageRect::Update();
	if (hiddenDeath)
	{
		SetAniamtion();
		HiddenDeathMove();
		animations[curType]->Update();
		isDeath = true;
		return;
	}

	Move();
	SetAniamtion();

	animations[curType]->Update();

}

//void Goomba::Render(HDC hdc)
//{
//	ImageRect::Render(hdc, animations[curType]->GetFrame());
//}

void Goomba::Move()
{
	if (isDeath) return;


	pos.x += speed * DELTA;
	gravity += GRAVITY * DELTA;
	 
	//ReturnMoveX();

	pos.y += gravity * DELTA;

}

void Goomba::SetAniamtion()
{
	if (hiddenDeath)
	{
		curType = HIDDENDEATH;
		SetAction(curType);
	}
	else if (!isDeath)
	{
		curType = IDLE;
		SetAction(curType);
	}	
	else
	{
		DeathTime += DELTA;
		curType = DEATH;
		SetAction(curType);
		
		if (DeathTime > DEATH_DELAY_TIME)
			isActive = false;
	}


}

void Goomba::CreateAnimation()
{
	if (isCave == false)
	{
		texture = TEXTURE->Add(L"Textures/Monster/Field/F_Goomba.bmp", 32, 32, 2, 2);
	}
	else
	{
		texture = TEXTURE->Add(L"Textures/Monster/Cave/C_GoomBa.bmp", 32, 32, 2, 2);
	}
	size = texture->GetSize() * 2.5f;

	animations[IDLE] = new Animation(texture->GetFrame(), 0.3f);
	animations[IDLE]->SetPart(0, 1, true);
	animations[DEATH] = new Animation(texture->GetFrame());
	animations[DEATH]->SetPart(2, 2, true);
	animations[HIDDENDEATH] = new Animation(texture->GetFrame());
	animations[HIDDENDEATH]->SetPart(3, 3, true);
	animations[curType]->Play();
}

//void Goomba::IsOnTheGround(Vector2 Ground)
//{
//	pos.y = Ground.y - Half().y;
//	gravity = 0;
//}
//
//void Goomba::SetAction(ActionType type)
//
//{
//	if (curType == type) return;
//
//	curType = type;
//	animations[type]->Play();
//
//}
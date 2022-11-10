#include "Framework.h"
#include "Tutle.h"

Tutle::Tutle()
{
	isActive = true;
	SetEvent(bind(&Tutle::ReturnAni, this));
}

Tutle::~Tutle()
{
	for (pair<ActionType, Animation*> animation : animations)
		delete animation.second;
	animations.clear();
}

void Tutle::ReturnAni()
{
	isLeft = isLeft ? false : true;
}

void Tutle::Update()
{
	//ImageRect::Update();
	if (!isActive)
	{
		pos = shell->Pos();
		return;
	}
	if (hiddenDeath)
	{
		//HiddenDeathMove();
		//animations[curType]->Update();
		//if (Top() > WIN_HEIGHT)
		isDeath = true;
		isActive = false;
		shell->Active() = true;
		shell->SetHiddenDeath();
		return;
	}
	Move();
	SetAniamtion();
	if (Top() > WIN_HEIGHT)
		isActive = false;


	animations[curType]->Update();
}

//void Tutle::Render(HDC hdc)
//{
//	//ImageRect::Render(hdc, animations[curType]->GetFrame());
//}

void Tutle::Move()
{
	if (!isActive) return;


	pos.x += speed * DELTA;
	gravity += GRAVITY * DELTA;

	//ReturnMoveX();

	pos.y += gravity * DELTA;
}

void Tutle::SetAniamtion()
{
	if (isDeath)
	{
		isActive = false;
		
		shell->Active() = true;

	}
	else if(isLeft)
	{
		SetAction(TUTLE_L);
	}
	else if(!isLeft)
	{
		SetAction(TUTLE_R);
	}
}

void Tutle::CreateAnimation()
{
	if (isCave == false)
	{
		texture = TEXTURE->Add(L"Textures/Monster/Field/F_Tutle.bmp", 32, 48, 2, 2);
		size = texture->GetSize() * 2.5f;

		animations[TUTLE_L] = new Animation(texture->GetFrame(), 0.3f);
		animations[TUTLE_L]->SetPart(0, 1, true);
		animations[TUTLE_R] = new Animation(texture->GetFrame(), 0.3f);
		animations[TUTLE_R]->SetPart(2, 3, true);
	}
	else
	{
		texture = TEXTURE->Add(L"Textures/Monster/Cave/C_Tutle.bmp", 32, 48, 2, 2);
		size = texture->GetSize() * 2.5f;

		animations[TUTLE_L] = new Animation(texture->GetFrame(), 0.3f);
		animations[TUTLE_L]->SetPart(0, 1, true);
		animations[TUTLE_R] = new Animation(texture->GetFrame(), 0.3f);
		animations[TUTLE_R]->SetPart(2, 3, true);
	}

	curType = TUTLE_R;
	animations[curType]->Play();
	shell = ShellManager::Get()->SetShell(this);
}

void Tutle::Resurection(Vector2 position)
{
	pos = position;
	SetAniamtion();
	isDeath = false;
	isActive = true;
	animations[curType]->Play();
}

void Tutle::SetShell()
{
	shell = ShellManager::Get()->SetShell(this);
}

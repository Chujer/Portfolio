#include "Framework.h"

Shell::Shell(Tutle* tutle)
{
	isActive = false;
	this->tutle = tutle;
	isCave = tutle->GetCave();
	pos = tutle->Pos();
	CreateAnimation();
	animations[curType]->Play();

	Audio::Get()->Add("Bump", "Sounds/Bump.wav");
}

Shell::~Shell()
{
	for (pair<ActionType, Animation*> animation : animations)
		delete animation.second;
	animations.clear();
}

void Shell::Render(HDC hdc)
{
	ImageRect::CamRender(hdc, animations[curType]->GetFrame());
}

void Shell::Update()
{
	//ImageRect::Update();
	if (!isAttack)
	{
		if (!isReady)
		{
			swapTime += DELTA;
			if (swapTime > WAITTIME)
			{
				swapTime = 0;
				isReady = true;
			}
		}
	}

	if (!isActive)
	{
		pos = tutle->Pos();
		return;
	}
	SetAniamtion();
	Move();

	thisTime += DELTA;
	if (thisTime > RESURRECTIONTIME)
	{
		thisTime -= RESURRECTIONTIME;
		tutle->Resurection(pos);
		isActive = false;
	}
}

void Shell::Move()
{
	gravity += GRAVITY * DELTA;
	if (hiddenDeath)
	{
		thisTime = 0;
		//isAttack = false;
		SetAniamtion();
		HiddenDeathMove();
		curType = HIDDENDEATH;

		if (Top() > WIN_HEIGHT)
			isActive = false;

		return;
	}

	if (isAttack)
	{
		thisTime = 0;
		pos += direction.Normalized() * speed * DELTA;
		//ReturnMoveX();
	}
	if (Top() > WIN_HEIGHT)
		isActive = false;
	pos.y += gravity * DELTA;
}

void Shell::IsOnTheGround(Vector2 Ground)
{
	if (hiddenDeath) return;

	pos.y = Ground.y - Half().y;
	gravity = 0;
}

void Shell::SetAction(ActionType type)
{
	if (curType == type) return;

	curType = type;
	animations[type]->Play();
}

void Shell::HiddenDeathMove()
{
	SetAction(HIDDENDEATH);
	if (justOne)
		HiddenDeathJump();
	float gravity = GRAVITY * DELTA;
	velocity += gravity * DELTA;
	pos.y += velocity;
}

void Shell::HiddenDeathJump()
{
	velocity = -300 * DELTA;
	justOne = false;
}

void Shell::SetPosition(Vector2 position)
{
	this->pos = position;
}

void Shell::ReturnMoveX()
{
	direction.x *= -1;
	Audio::Get()->Play("Bump",0.6f);
}


void Shell::SetAniamtion()
{
	if (curType == HIDDENDEATH)
	{
		SetAction(curType);
	}
	else if (thisTime > RESURRECTIONTIME * 0.8f)
	{
		curType = RESURRECTION;
		SetAction(curType);
	}
	else
	{
		curType = IDLE;
		SetAction(curType);
	}
}

void Shell::CreateAnimation()
{
	if (isCave == false)
	{
		texture = TEXTURE->Add(L"Textures/Monster/Field/F_Shell.bmp", 32, 32, 2, 2);
	}
	else
	{
		texture = TEXTURE->Add(L"Textures/Monster/Cave/C_Shell.bmp", 32, 32, 2, 2);
	}
	size = texture->GetSize() * 2.5f;

	animations[IDLE] = new Animation(texture->GetFrame(), 0.3f);
	animations[IDLE]->SetPart(0, 0, true);
	animations[RESURRECTION] = new Animation(texture->GetFrame());
	animations[RESURRECTION]->SetPart(1, 1, true);
	animations[HIDDENDEATH] = new Animation(texture->GetFrame());
	animations[HIDDENDEATH]->SetPart(2, 2, true);
	camRect->Size() = size;
}

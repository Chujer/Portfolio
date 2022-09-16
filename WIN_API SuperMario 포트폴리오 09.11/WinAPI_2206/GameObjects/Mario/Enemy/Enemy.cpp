#include "Framework.h"

Enemy::Enemy()
{
	/*CreateAnimation();

	animations[curType]->Play();*/
	isActive = false;
}

Enemy::~Enemy()
{
	for (pair<ActionType, Animation*> animation : animations)
		delete animation.second;
	animations.clear();
}


void Enemy::Render(HDC hdc)
{
	ImageRect::CamRender(hdc, animations[curType]->GetFrame());
}

void Enemy::Move()
{
	if (isDeath) return;

	pos.x += speed * DELTA;
	gravity += GRAVITY * DELTA;


	pos.y += gravity * DELTA;
}



void Enemy::IsOnTheGround(Vector2 Ground)
{
	if (hiddenDeath) return;
	//pos.y = Ground.y - Half().y;
	gravity = 0;
}


void Enemy::SetAction(ActionType type)
{
	if (curType == type) return;

	curType = type;
	animations[type]->Play();
}

void Enemy::HiddenDeathMove()
{
	SetAction(HIDDENDEATH);
	if (justOne)
		HiddenDeathJump();
	float gravity = GRAVITY * DELTA;
	velocity += gravity * DELTA;
	pos.y += velocity;
}

void Enemy::HiddenDeathJump()
{
	velocity = -300 * DELTA;
	justOne = false;
}

void Enemy::SetPosition(Vector2 position)
{
	this->pos = position;
	camRect->Size() = size;
}

void Enemy::ReturnMoveX()
{
	speed *= -1;
	if (Event != nullptr )		
	{
		Event();
	}
}


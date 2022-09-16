#include "Framework.h"

Bullet::Bullet()
{
	SetTexture(TEXTURE->Add(L"Textures/newMario/Bullet/Bullet.bmp", 32, 8, 4, 1));
	size = texture->GetSize() * 3.0f;
	camRect->Size() = size;
	animation = new Animation(texture->GetFrame());
	animation->SetPart(0, 3, true);
	isActive = false;
}

Bullet::~Bullet()
{
	delete animation;
}

void Bullet::Update()
{
	if (!isActive) return;

	if (isTuchGround)
		Move();
	else
		StartMove();
	animation->Update();
	EnemyManager::Get()->IsCollisionBulletToEnemy(this);
}

void Bullet::Render(HDC hdc)
{
	if (!isActive) return;

	ImageRect::CamRender(hdc, animation->GetFrame());
}

void Bullet::CreateBullet(Vector2 position, bool isRight)
{
	if (isRight)
	{
		pos = position;
		pos.x = position.x+35.0f;
		speed = 700.0f;
	}
	else
	{
		pos = position;
		pos.x = position.x - 35.0f;
		speed = -700.0f;
	}

	gravity = 0;
	velocity = { 0,0 };
	isActive = true;
	animation->Play();
	isTuchGround = false;
}

void Bullet::Move()
{
	gravity += GRAVITY *4 * DELTA;
	velocity += Vector2(speed, gravity) * DELTA;

	
	pos.x += speed * DELTA;
	pos.y += velocity.y * DELTA;
}

void Bullet::StartMove()
{
	pos.x += speed * DELTA;
	pos.y += abs(speed)*0.5f * DELTA;
}

void Bullet::IsCollisionGround()
{
	gravity = 0;
	velocity.y = -BOUND_FOWER;
	isTuchGround = true;
}

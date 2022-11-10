#include "Framework.h"

Mushroom::Mushroom()
{
	SetEvent(MarioEventManager::Get()->GetEvent("EatMushroom"));
}

Mushroom::~Mushroom()
{
}

void Mushroom::Move()
{
	if (!isActive) return;

	if (!arrivalDestination)
	{
		pos.y -= speed * DELTA;
		if (pos.y < destination.y-10.0f)
			arrivalDestination = true;
	}

	if (arrivalDestination)
	{
		pos.x += speed * DELTA;
		gravity += GRAVITY * DELTA;

		//if (Left() < 0 || Right() > WIN_WIDTH)
		//	speed *= -1;

		pos.y += gravity * DELTA;
	}
}

void Mushroom::SetItemTexture()
{
	SetTexture(TEXTURE->Add(L"Textures/Item/Mushroom.bmp", 16, 16, 1, 1));
	SetSize();
}

void Mushroom::IsOnTheGround(Vector2 Ground)
{
	if (!arrivalDestination)return;
	pos.y = Ground.y - Half().y;
	gravity = 0;
}

void Mushroom::StartSound()
{
	Audio::Get()->Play("Item", 0.7f);
}

#include "Framework.h"

Flower::Flower()
{
	SetEvent(MarioEventManager::Get()->GetEvent("EatFlower"));
}

Flower::~Flower()
{
}

void Flower::Move()
{
	if (!isActive) return;

	if (!arrivalDestination)
	{
		pos.y -= speed * DELTA;
		if (pos.y < destination.y)
			arrivalDestination = true;
	}
}

void Flower::SetItemTexture()
{
	SetTexture(TEXTURE->Add(L"Textures/Item/Flower.bmp", 16, 16, 1, 1));
	SetSize();
}

void Flower::IsOnTheGround(Vector2 Ground)
{
}
void Flower::StartSound()
{
	Audio::Get()->Play("Item", 0.7f);
}


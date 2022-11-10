#include "Framework.h"

Coin::Coin()
{
	speed = 600.0f;
}

Coin::~Coin()
{
}

void Coin::Move()
{
	if (!isActive) return;
	if (startAni == false)
	{
		ani->Play();
		startAni = true;
	}

	if (!arrivalDestination)
	{
		//pos.y = LERP(pos.y, destination.y-1, speed * DELTA);
		pos.y -= speed * DELTA;
		if (pos.y < destination.y - 80)
		{
			arrivalDestination = true;
			MarioGameManager::Get()->Coin()++;
			MarioGameManager::Get()->Score() += 200;
		}
	}
	else
	{
		if (pos.y > destination.y)
		{
			isActive = false;
		}
		else
		{
			//pos.y = LERP(pos.y, destination.y + 40, speed * DELTA);
			pos.y += speed * DELTA;
		}
	}
	ani->Update();
}

void Coin::SetItemTexture()
{
	SetTexture(TEXTURE->Add(L"Textures/Item/coin.bmp", 112, 16, 7, 1));
	ani = new Animation(texture->GetFrame(),0.1f);
	ani->SetPart(0, 6, true);
	ani->Play();
	SetSize();
}

void Coin::Render(HDC hdc)
{
	ImageRect::CamRender(hdc, ani->GetFrame());
}

void Coin::IsOnTheGround(Vector2 Ground)
{
}

void Coin::StartSound()
{
	Audio::Get()->Play("Coin", 0.7f);
}

void Coin::AniUpdate()
{
	ani->Update();
}


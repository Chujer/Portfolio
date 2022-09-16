#include "Framework.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Update()
{
	Move();
}

void Item::Render(HDC hdc)
{
	ImageRect::CamRender(hdc);
}


void Item::SetItemTexture()
{
	SetTexture(TEXTURE->Add(L"Textures/Mario/Itemp.bmp", 18, 18, 1, 1));
	size = texture->GetSize() * 2.5f;
}

void Item::IsOnTheGround(Vector2 Ground)
{
	pos.y = Ground.y - Half().y;
	gravity = 0;
}

void Item::CreateItem(Vector2 pos, Vector2 destination)
{
	SetItemTexture();
	this->pos = pos;
	this->destination = destination;
	isActive = true;
}

#include "Framework.h"

ItemBlockTile::ItemBlockTile()
{
	//CreateAnimation();

}

ItemBlockTile::~ItemBlockTile()
{
	delete item;
}

void ItemBlockTile::Update()
{
	Tile::Update();
	item->Update();
	animations[state]->Update();
}

void ItemBlockTile::Render(HDC hdc)
{
	if (item->Active() == true)
		item->Render(hdc);

	ImageRect::CamRender(hdc,animations[state]->GetFrame());

}

void ItemBlockTile::CreateBlock(Vector2 pos)
{
	this->pos = pos;
}

void ItemBlockTile::CreateAnimation()
{

	animations[USE] = new Animation(texture->GetFrame(),0.3f);
	animations[USE]->SetPart(0, 2, true);

	animations[USED] = new Animation(texture->GetFrame());
	animations[USED]->SetPart(3, 3, true);

	animations[state]->Play();
	
}

void ItemBlockTile::SetItem(string name)
{
	if (name == "Mushroom")
		item = new Mushroom();

	else if (name == "Flower")
		item = new Flower();

	else if (name == "Coin1")
		item = new Coin();

	item->Active() = false;
	item->Pos() = pos;
	
}

void ItemBlockTile::MakeItem()
{
	if (state == USE)
	{
		SetAction(USED);
		item->CreateItem(pos, { pos.x, pos.y - 50.0f });
		item->StartSound();
	}
}

void ItemBlockTile::SetAction(State type)
{
	if (state == type) return;

	state = type;
	animations[type]->Play();
}

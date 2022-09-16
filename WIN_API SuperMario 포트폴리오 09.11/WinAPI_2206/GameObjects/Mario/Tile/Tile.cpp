#include "Framework.h"

Tile::Tile()
{
	selectPen = CreatePen(PS_SOLID, 1, RED);
	oldPen = CreatePen(PS_NULL, 1, NULL_PEN);
	SetTexture("NONE");
	tileInfo.tag = TAG::NONE;
}

Tile::~Tile()
{
	DeleteObject(selectPen);
	DeleteObject(oldPen);
};

void Tile::Update()
{
}

void Tile::Render(HDC hdc)
{
	ImageRect::CamRender(hdc);

	if (selectTile)
		SelectObject(hdc, selectPen);
	else
		SelectObject(hdc, oldPen);

	Rect::LineRender(hdc);
	
}

void Tile::NomalRender(HDC hdc)
{
	ImageRect::Render(hdc);
	if (selectTile)
		SelectObject(hdc, selectPen);
	else
		SelectObject(hdc, oldPen);

	Rect::LineRender(hdc);
}

void Tile::TileMove()
{
	ImageRect::Update();
}

void Tile::CreateTile(Vector2 pos, int textureNum)
{

	tileInfo.tileName = TileTextureData::Get()->GetTileInfo(textureNum).tileName;
	tileInfo.tag = TileTextureData::Get()->GetTileInfo(textureNum).tag;
	SetTexture(tileInfo.tileName);
	SetPos(pos);

}

void Tile::CreateTile(Vector2 pos, string name, TAG tag, string itemName)
{
	tileInfo.tileName = name;
	tileInfo.tag = tag;
	SetTexture(tileInfo.tileName);
	SetPos(pos);
	if (tag == TAG::ITEMBLOCK)
		SetItem(itemName);
}

void Tile::Break()
{
	isActive = false;
}

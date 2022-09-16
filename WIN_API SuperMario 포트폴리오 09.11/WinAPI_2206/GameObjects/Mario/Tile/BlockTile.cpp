#include "Framework.h"

BlockTile::BlockTile()
{
	SetTexture("F_IndestructibleBlock");
}

BlockTile::~BlockTile()
{
}

void BlockTile::Render(HDC hdc)
{
	ImageRect::CamRender(hdc);
}

void BlockTile::Break()
{
	if (tileInfo.tileName == "F_NomalBlock")
	{
		CreateTile(pos, "Sky", TAG::BACKGROUND, "Sky");
	}
	else if (tileInfo.tileName == "C_NomalBlock")
	{
		CreateTile(pos, "CaveSkey", TAG::BACKGROUND, "CaveSkey");
	}
}

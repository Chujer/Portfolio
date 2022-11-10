#include "Framework.h"
#include "TileTextureData.h"

TileTextureData::TileTextureData()
{
	CreateTexture();
}

TileTextureData::~TileTextureData()
{
}

void TileTextureData::CreateTexture()
{
	//NONE
	SetTexture(L"Textures/ImageTile/BackGround/NONE.bmp","NONE",NONE);
	//BackGround
	SetTexture(L"Textures/ImageTile/BackGround/Sky.bmp", "Sky", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/CaveSky.bmp","CaveSkey", BACKGROUND);

		//Castle
	SetTexture(L"Textures/ImageTile/BackGround/Castle001.bmp", "Castle001", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Castle002.bmp", "Castle002", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Castle003.bmp", "Castle003", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Castle004.bmp", "Castle004", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Castle005.bmp", "Castle005", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Castle006.bmp", "Castle006", BACKGROUND);
		//Cloude
	SetTexture(L"Textures/ImageTile/BackGround/Cloude001.bmp", "Cloude001", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Cloude002.bmp", "Cloude002", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Cloude003.bmp", "Cloude003", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Cloude004.bmp", "Cloude004", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Cloude005.bmp", "Cloude005", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Cloude006.bmp", "Cloude006", BACKGROUND);

		//Flag
	SetTexture(L"Textures/ImageTile/BackGround/Flag.bmp", "Flag", EVENT);
	SetTexture(L"Textures/ImageTile/BackGround/FlagBall.bmp", "FlagBall", EVENT);
	SetTexture(L"Textures/ImageTile/BackGround/FlagBar.bmp", "FlagBar", EVENT);

		//Grass
	SetTexture(L"Textures/ImageTile/BackGround/Grass001.bmp", "Grass001", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Grass002.bmp", "Grass002", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Grass003.bmp", "Grass003", BACKGROUND);

		//Mountain
	SetTexture(L"Textures/ImageTile/BackGround/Mountain001.bmp", "Mountain001", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Mountain002.bmp", "Mountain002", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Mountain003.bmp", "Mountain003", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Mountain004.bmp", "Mountain004", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Mountain005.bmp", "Mountain005", BACKGROUND);
	SetTexture(L"Textures/ImageTile/BackGround/Mountain006.bmp", "Mountain006", BACKGROUND);

	//Field
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Ground.bmp", "F_Ground", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_IndestructibleBlock.bmp", "F_IndestructibleBlock", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_NomalBlock.bmp", "F_NomalBlock", BLOCK);
		
		//Pipe
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe001.bmp", "F_Pipe001", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe002.bmp", "F_Pipe002", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe003.bmp", "F_Pipe003", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe004.bmp", "F_Pipe004", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe005.bmp", "F_Pipe005", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe006.bmp", "F_Pipe006", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe007.bmp", "F_Pipe007", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe008.bmp", "F_Pipe008", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe009.bmp", "F_Pipe009", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_Pipe010.bmp", "F_Pipe010", INDESTRUCTIBLE_BLOCK);

	SetTexture(L"Textures/ImageTile/GroundPalette/F_ItemBlock.bmp", "F_ItemBlock", ITEMBLOCK, 64, 16, 4, 1);
	SetTexture(L"Textures/ImageTile/GroundPalette/F_UsedItemBlock.bmp", "F_UsedItemBlock", INDESTRUCTIBLE_BLOCK);

	//Cave
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Ground.bmp", "C_Ground", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_IndestructibleBlock.bmp", "C_IndestructibleBlock", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_NomalBlock.bmp", "C_NomalBlock", BLOCK);

	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe001.bmp", "C_Pipe001", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe002.bmp", "C_Pipe002", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe003.bmp", "C_Pipe003", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe004.bmp", "C_Pipe004", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe005.bmp", "C_Pipe005", EVENT);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe006.bmp", "C_Pipe006", EVENT);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe007.bmp", "C_Pipe007", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe008.bmp", "C_Pipe008", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe009.bmp", "C_Pipe009", INDESTRUCTIBLE_BLOCK);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_Pipe010.bmp", "C_Pipe010", INDESTRUCTIBLE_BLOCK);

	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_ItemBlock.bmp", "C_ItemBlock", ITEMBLOCK, 64, 16,4,1);
	SetTexture(L"Textures/ImageTile/UndergroundPalette/C_UsedItemBlock.bmp", "C_UsedItemBlock", INDESTRUCTIBLE_BLOCK);

	SetTexture(L"Textures/ImageTile/BossStage/B_bridge.bmp", "B_bridge", EVENT);
	SetTexture(L"Textures/ImageTile/BossStage/B_Chain.bmp", "B_Chain", EVENT);
	SetTexture(L"Textures/ImageTile/BossStage/B_Exe.bmp", "B_Exe", EVENT, 48, 16,3,1);
	SetTexture(L"Textures/ImageTile/BossStage/B_Ground.bmp", "B_Ground", EVENT);	

	SetTexture(L"Textures/ImageTile/Player.bmp", "Player", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/Boss1.bmp", "Boss1", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/F_Goomba1.bmp", "F_Goomba1", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/C_Goomba1.bmp", "C_Goomba1", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/F_Tutle1.bmp", "F_Tutle1", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/C_Tutle1.bmp", "C_Tutle1", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/F_Flower1.bmp", "F_Flower1", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/C_Flower1.bmp", "C_Flower1", CHARACTER);
	SetTexture(L"Textures/ImageTile/Enemy/F_FlyTutle1.bmp", "F_FlyTutle1", CHARACTER);

	SetTexture(L"Textures/Item/Mushroom.bmp", "Mushroom", ITEM);
	SetTexture(L"Textures/Item/Flower.bmp", "Flower", ITEM);
	SetTexture(L"Textures/Item/Coin1.bmp", "Coin1", ITEM);
}

void TileTextureData::SetTexture(wstring file, string key, TAG tag)
{
	if (textures.find(key) != textures.end()) return;
	texture = TEXTURE->Add(file, 16, 16);
	textures[key] = texture;
	
	tileInfo[tileCount].tileName = key;
	tileInfo[tileCount].tag = tag;
	tileCount++;
}

void TileTextureData::SetTexture(wstring file, string key, TAG tag, int sizeX, int sizeY, int frameX, int frameY)
{
	if (textures.find(key) != textures.end()) return;
	texture = TEXTURE->Add(file, sizeX, sizeY, frameX, frameY);
	textures[key] = texture;
	tileInfo[tileCount].tileName = key;
	tileInfo[tileCount].tag = tag;
	tileCount++;
}

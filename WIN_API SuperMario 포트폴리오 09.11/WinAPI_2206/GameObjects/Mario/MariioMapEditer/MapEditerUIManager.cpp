#include "Framework.h"

MapEditerUIManager::MapEditerUIManager()
{
	CreatePanel();
	CreateUITile();
}

MapEditerUIManager::~MapEditerUIManager()
{
	delete panel;
	delete tempPanelInfo;
}

void MapEditerUIManager::Update()
{
	MovePanel();
	MoveUITile();
}

void MapEditerUIManager::Render(HDC hdc)
{
	panel->Render(hdc, 50);
	for (Tile* tile : tiles)
	{
		tile->NomalRender(hdc);
	}
}

void MapEditerUIManager::MovePanel()
{
	if (KEY_DOWN(VK_F2))
	{
		if (isOpen)
			isOpen = false;
		else
			isOpen = true;
	}

	if (isOpen)
		panel->Pos().x = LERP(panel->Pos().x, firstPanelPos.x, 3.0f * DELTA);
	else
		panel->Pos().x = LERP(panel->Pos().x, firstPanelPos.x + panel->Size().x, 3.0f * DELTA);

	panelLT = { panel->Left(), panel->Top() };
}

void MapEditerUIManager::CreatePanel()
{
	tempPanelInfo = new Rect(WIN_WIDTH * 0.6f, 0, WIN_WIDTH + 1, WIN_HEIGHT* 2);
	panel = new ImageRect(TEXTURE->Add(L"Textures/UIpanel.bmp", 100, 100));
	panel->Pos() = tempPanelInfo->Pos();
	firstPanelPos = panel->Pos();
	panel->Pos().x += panel->Pos().x + panel->Size().x;
	panel->Size() = tempPanelInfo->Size();
	panelLT = { panel->Left(), panel->Top() };
	panelMovePoint = panel->Pos();
}

void MapEditerUIManager::CreateUITile()
{
	int temp = TileTextureData::Get()->GetTileCount() - 1;
	tiles.resize(temp);
	int tempY = 0;
	int tempX = 0;

	for (int i = 1; i < TileTextureData::Get()->GetTileCount(); i++)
	{
		int tempnum = i - 1;
		tiles[tempnum] = new Tile();
		tiles[tempnum]->CreateTile({ (panelLT.x + tiles[tempnum]->Half().x + offset.x) + ((tiles[tempnum]->Size().x + offset.x) * tempX) ,
			(panelLT.y + offset.y + tiles[tempnum]->Half().y) + ((tiles[tempnum]->Size().y + offset.y) * tempY) }, i);
		tempX++;
		if (tiles[tempnum]->Pos().x + tiles[tempnum]->Size().x + offset.x > panel->Right())
		{
			tempY++;
			tempX = 0;
		}
	}
}

void MapEditerUIManager::MoveUITile()
{
	if (panelMovePoint != panel->Pos())
	{
		for (Tile* tile : tiles)
		{
			tile->Pos() -= panelMovePoint - panel->Pos();
		}
		panelMovePoint = panel->Pos();
	}
}
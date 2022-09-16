#include "Framework.h"

TileMapManager::TileMapManager()
{
	moveCamPos = Camera::Get()->GetPos();
	//시작시 투명타일 배치
	selectTile.tileName = "NONE";
	tiles.resize(MAX_TILE);
	for (Tile*& tile : tiles)
	{
		tile = new Tile();
		tile->CreateTile(tilePos, 0);
		tilePos = Vector2((tileCountX * tile->Size().x) + tile->Half().x, 
			((tileCountY * tile->Size().y) + tile->Half().y) - tile->Half().y);
		tile->SetPos(tilePos);
		tileCountX++;
		if (tileCountX == MAX_TILE_X)
		{
			tileCountY++;
			tileCountX = 0;
		}
	}
}

TileMapManager::~TileMapManager()
{
	if (isEditer)
	{
		for (Tile* tile : tiles)
		{
			tile->Pos() = tile->Pos() + moveCamPos;
			if (tile->TileInfo().tag != TAG::NONE)
			{
				MarioDataManager::Get()->SetTileData(tile);
			}
			delete tile;
		}
		tiles.clear();
		for (Tile* tile : characterTiles)
		{
			tile->Pos() = tile->Pos() + moveCamPos;
			MarioDataManager::Get()->SetCharacterData(tile);
			delete tile;
		}
		characterTiles.clear();
		for (Tile* tile : itemTiles)
		{
			tile->Pos() = tile->Pos() + moveCamPos;
			MarioDataManager::Get()->SetItemData(tile);
			delete tile;
		}
		itemTiles.clear();
		MarioDataManager::Get()->SaveMapData();
		MarioDataManager::Get()->SaveCharacterData();
		MarioDataManager::Get()->SaveItemData();
	}
	else
	{
		for (Tile* tile : tiles)
		{
			tile->Pos() = tile->Pos() + moveCamPos;
			delete tile;
		}
		tiles.clear();
		for (Tile* tile : characterTiles)
		{
			tile->Pos() = tile->Pos() + moveCamPos;
			delete tile;
		}
		characterTiles.clear();
		for (Tile* tile : itemTiles)
		{
			tile->Pos() = tile->Pos() + moveCamPos;
			delete tile;
		}
		itemTiles.clear();
	}
}

void TileMapManager::LoadTileData(MarioDataManager::TileData data)
{
	Tile* tile = new Tile();
	tile->CreateTile(Vector2(data.positionX, data.positionY), data.name, (TAG)data.tag, data.name);
	tiles.push_back(tile);
}
void TileMapManager::LoadCharacterData(MarioDataManager::CharacterData data)
{
	characterTiles.push_back(new Tile());
	characterTiles[characterCount]->Pos() = { data.positionX,data.positionY };
	characterTiles[characterCount++]->SetTexture(data.name);
}
void TileMapManager::Update()
{
	moveCamPos = Camera::Get()->GetPos();
	if (KEY_DOWN(VK_SPACE))
	{
		tiles.clear();
		MarioDataManager::Get()->LoadEditerStage("TextData/Stage3.");
	}
	for (Tile* tile : tiles)
	{
		tile->TileMove();
	}
	for (Tile* tile : characterTiles)
	{
		tile->TileMove();
	}
	for (Tile* tile : itemTiles)
	{
		tile->TileMove();
	}
	SelectMapTile();
	MoveTileUI();

	//타일UI의 타일 선택
	for (Tile* pTile : MapEditerUIManager::Get()->GetTile())
	{
		if (pTile->IsCollision(mousePos))
		{
			pTile->select() = true;
			if (KEY_DOWN(VK_LBUTTON))
			{
				isEditer = true;
				selectTile = pTile->TileInfo();
			}
		}
		else
			pTile->select() = false;
	}
}

void TileMapManager::Render(HDC hdc)
{
	for (Tile* tile : tiles)
	{
		tile->NomalRender(hdc);
	}
	for (Tile* tile : characterTiles)
	{
		tile->NomalRender(hdc);
	}
	for (Tile* tile : itemTiles)
	{
		tile->NomalRender(hdc);
	}
}

//선택한 타일 맵에 배치함수
void TileMapManager::SelectMapTile()
{
	for (Tile* tile : tiles)
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			if (MapEditerUIManager::Get()->GetPanel()->IsCollision(mousePos))	// UI창클릭시 예외처리
				break;
			if (tile->IsCollision(mousePos))
			{
				if (tile->TileInfo().tileName != selectTile.tileName)
				{
					if (selectTile.tag == TAG::CHARACTER)
					{
						characterTiles.push_back(new Tile());
						characterTiles[characterCount]->Pos() = tile->Pos() + moveCamPos;
						characterTiles[characterCount++]->SetTexture(selectTile.tileName);
					}
					else if (selectTile.tag == TAG::ITEM && tile->TileInfo().tag == TAG::ITEMBLOCK)
					{
						itemTiles.push_back(new Tile());
						itemTiles[itemCount]->Pos() = tile->Pos() + moveCamPos;
						itemTiles[itemCount++]->SetTexture(selectTile.tileName);
					}
				}
			}
		}
		else if (KEY_PRESS(VK_LBUTTON))
		{
			if (MapEditerUIManager::Get()->GetPanel()->IsCollision(mousePos))
				break;
			if (tile->IsCollision(mousePos))
			{
				if (tile->TileInfo().tileName != selectTile.tileName)
				{
					if (selectTile.tag == TAG::CHARACTER || selectTile.tag == TAG::ITEM)
					{
					}
					else
					{
						//클릭한 타일을 저장한 타일정보로 변경
						tile->SetTexture(selectTile.tileName);
						tile->TileInfo().tag = selectTile.tag;
					}
				}
			}
		}
	}
	for (Tile* tile : tiles)	
	{
		if (tile->IsCollision(mousePos))
		{
			if (MapEditerUIManager::Get()->GetPanel()->IsCollision(mousePos))
			{
				tile->select() = false;
				break;
			}
			if (!tile->select())
			{
				tile->select() = true;
				break;
			}
		}
		else
			tile->select() = false;
	}
}

void TileMapManager::MoveTileUI()
{
	if (MapEditerUIManager::Get()->GetPanel()->IsCollision(mousePos))
	{
		if (KEY_PRESS(VK_RBUTTON) && KEY_PRESS('S'))
		{
			if (MapEditerUIManager::Get()->GetPanel()->Top() > 0) return;
			MapEditerUIManager::Get()->GetPanel()->Pos().y += 200.0f * DELTA;
		}
		if (KEY_PRESS(VK_RBUTTON) && KEY_PRESS('W'))
			MapEditerUIManager::Get()->GetPanel()->Pos().y -= 200.0f * DELTA;
	}
}

void TileMapManager::SetSelectTile(Tile* tile)
{
	selectTile = tile->TileInfo();
}


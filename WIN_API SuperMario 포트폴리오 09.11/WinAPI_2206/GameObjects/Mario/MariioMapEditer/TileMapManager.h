#pragma once

class TileMapManager : public Singleton<TileMapManager>
{
private:
	const UINT MAX_TILE = 2865;
	const UINT MAX_TILE_X = 191;
	const UINT MAX_TILE_Y = 14;
	


public:
	TileMapManager();
	~TileMapManager();

	void Update();
	void Render(HDC hdc);
	void SelectMapTile();
	void MoveTileUI();

	void SetSelectTile(Tile* tile);

	void LoadTileData(MarioDataManager::TileData data);
	void LoadCharacterData(MarioDataManager::CharacterData data);

private:
	vector<Tile*> tiles;
	vector<Tile*> characterTiles;
	vector<Tile*> itemTiles;
	UINT tileCount = 0;
	UINT tileCountX = 0;
	UINT tileCountY = 0;
	Vector2 tilePos;
	int characterCount = 0;
	int itemCount = 0;
	TileData selectTile;

	Vector2 moveCamPos;
	bool isEditer = false;
};
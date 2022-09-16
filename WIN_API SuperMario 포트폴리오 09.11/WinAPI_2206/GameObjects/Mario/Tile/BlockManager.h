#pragma once

class BlockManager : public Singleton<BlockManager>
{
public:
	BlockManager();
	~BlockManager();

	void Update();
	void Render(HDC hdc);

	void CreateStage(MarioDataManager::TileData data, string ItemName = "");
	void CreateBackgroundTiles(MarioDataManager::TileData data);
	void CreateEventTiles(MarioDataManager::TileData data);
	void CreateindestructibleGroundBlocks(MarioDataManager::TileData data);
	void CreateNomalBlocks(MarioDataManager::TileData data);
	void CreateItemBlocks(MarioDataManager::TileData data, string ItemName);
	

	void IsCollisionBlockToPlayer(Mario* mario);
	void IsCollisionEventTileToPlayer(Mario* mario);
	void IsCollisionBlockToEnemy(Enemy* enemy);
	void IsCollisionItemBlockToPlayer(Mario* mario);
	void IsCollisionBlockToItem(Item* item);
	void IsCollisionItemToPlayer(Mario* mario);
	void IsCollisionBlockToShell(Shell* enemy);
	void IsCollisionBlockToBullet(Bullet* bullet);

private:
	vector<BlockTile*> indestructibleGroundBlocks;
	vector<BlockTile*> nomalBlock;
	vector<ItemBlockTile*> itemBlocks;
	vector<EventTile*> eventTiles;
	vector<Tile*> backgroundTiles;
	Vector2 overlap;
};
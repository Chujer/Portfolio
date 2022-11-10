#pragma once

class MarioDataManager : public Singleton<MarioDataManager>
{
public:
	//enum ItemTag
	//{
	//	NONE, MUSHROOM, FLOWER, COIN
	//};

	struct TileData
	{
		string name;
		float positionX;
		float positionY;
		int tag;
		//int itemTag;
	};

	struct CharacterData
	{
		string name;
		float positionX;
		float positionY;
	};

public:
	MarioDataManager();
	~MarioDataManager();

	void SetTileData(Tile* tile);
	void SetCharacterData(Tile* tile);
	void SetItemData(Tile* tile);

	void SaveMapData();
	void SaveCharacterData();
	void SaveItemData();
	
	void SetStage(string stageName);
	void LoadEditerStage(string stageName);

	void LoadMapData(string name);
	void LoadCharacterData(string name);
	void LoadItemData(string name);

	CharacterData GetPlayerData() { return playerData; }

private:
	vector<TileData> saveTileData;
	vector<CharacterData> saveCharacterData;
	vector<CharacterData> saveItemData;

	string fileName = "TextData/Stage3.";
	string nameMap = "map";
	string nameCharacter = "character";
	string nameItem = "item";

	vector<TileData> loadTileData;
	vector<CharacterData> loadCharacterData;
	vector<CharacterData> loadItemData;

	CharacterData playerData;
};
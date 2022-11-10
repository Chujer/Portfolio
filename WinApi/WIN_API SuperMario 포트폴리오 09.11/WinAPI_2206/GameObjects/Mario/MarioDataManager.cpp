#include "Framework.h"

MarioDataManager::MarioDataManager()
{
}

MarioDataManager::~MarioDataManager()
{
}

void MarioDataManager::SetTileData(Tile* tile)
{
	TileData tempTileData;

	tempTileData.name = tile->GetTileInfo().tileName;
	tempTileData.positionX = tile->Pos().x;
	tempTileData.positionY = tile->Pos().y;
	tempTileData.tag = tile->GetTileInfo().tag;

	saveTileData.push_back(tempTileData);
}

void MarioDataManager::SetCharacterData(Tile* tile)
{
	CharacterData tempData;
	tempData.name = tile->GetTileInfo().tileName;
	tempData.positionX = tile->Pos().x;
	tempData.positionY = tile->Pos().y;

	saveCharacterData.push_back(tempData);
}

void MarioDataManager::SetItemData(Tile* tile)
{
	CharacterData tempData;
	tempData.name = tile->GetTileInfo().tileName;
	tempData.positionX = tile->Pos().x;
	tempData.positionY = tile->Pos().y;

	saveItemData.push_back(tempData);
}

void MarioDataManager::SaveMapData()
{
	BinaryWriter* writer = new BinaryWriter(fileName+nameMap);

	writer->UInt(saveTileData.size());

	for (TileData data : saveTileData)
	{
		writer->String(data.name);
		writer->Float(data.positionX);
		writer->Float(data.positionY);
		writer->Int(data.tag);
	}

	delete writer;
}

void MarioDataManager::SaveCharacterData()
{
	BinaryWriter* writer = new BinaryWriter(fileName+nameCharacter);

	writer->UInt(saveCharacterData.size());

	for (CharacterData data : saveCharacterData)
	{
		writer->String(data.name);
		writer->Float(data.positionX);
		writer->Float(data.positionY);
	}

	delete writer;
}

void MarioDataManager::SaveItemData()
{
	BinaryWriter* writer = new BinaryWriter(fileName + nameItem);

	writer->UInt(saveItemData.size());

	for (CharacterData data : saveItemData)
	{
		writer->String(data.name);
		writer->Float(data.positionX);
		writer->Float(data.positionY);
	}

	delete writer;
}

void MarioDataManager::LoadMapData(string name)
{
	BinaryReader* reader = new BinaryReader(name+nameMap);
	
	
	loadTileData.clear();
	loadTileData.resize(reader->UInt());

	for (TileData& tempTileData : loadTileData) 
	{
		tempTileData.name = reader->String();
		tempTileData.positionX = reader->Float();
		tempTileData.positionY = reader->Float();
		tempTileData.tag = reader->Int();
	}
	
	delete reader;
}

void MarioDataManager::LoadCharacterData(string name)
{
	BinaryReader* reader = new BinaryReader(name+nameCharacter);

	int tempCharacterCount = reader->UInt();

	loadCharacterData.clear();
	loadCharacterData.resize(tempCharacterCount);

	if(tempCharacterCount != 0)
		EnemyManager::Get()->SetEnemyCount(tempCharacterCount-1);

	for (CharacterData& tempCharacterData : loadCharacterData)
	{
		tempCharacterData.name = reader->String();
		tempCharacterData.positionX = reader->Float();
		tempCharacterData.positionY = reader->Float();
	}

	delete reader;
}

void MarioDataManager::LoadItemData(string name)
{
	BinaryReader* reader = new BinaryReader(name + nameItem);


	loadItemData.clear();
	loadItemData.resize(reader->UInt());

	for (CharacterData& tempItemData : loadItemData)
	{
		tempItemData.name = reader->String();
		tempItemData.positionX = reader->Float();
		tempItemData.positionY = reader->Float();
	}

	delete reader;
}

void MarioDataManager::SetStage(string stageName)
{
	LoadMapData(stageName);
	LoadCharacterData(stageName);
	LoadItemData(stageName);
	for (TileData data : loadTileData)		// 맵 생성
	{
		if (data.tag == TileTextureData::TAG::ITEMBLOCK)	//아이템 블럭 생성및 연결
		{
			for (CharacterData itemdata : loadItemData)
			{
				if (data.positionX == itemdata.positionX && data.positionY == itemdata.positionY)
				{
					BlockManager::Get()->CreateStage(data,itemdata.name);
					break;
				}
			}
		}
		else
			BlockManager::Get()->CreateStage(data);
	}
	for (CharacterData data : loadCharacterData)	//캐릭터 생성
	{
		if (data.name == "Player")
		{
			playerData = data;
		}
		else
		{
			if (data.name == "F_Goomba1")
				EnemyManager::Get()->CreateEnemy(EnemyManager::F_GOOMBA, { data.positionX,data.positionY });
			else if (data.name == "C_Goomba1")
				EnemyManager::Get()->CreateEnemy(EnemyManager::C_GOOMBA, { data.positionX,data.positionY });
			else if (data.name == "F_Tutle1")
				EnemyManager::Get()->CreateEnemy(EnemyManager::F_TUTLE, { data.positionX,data.positionY });
			else if (data.name == "C_Tutle1")
				EnemyManager::Get()->CreateEnemy(EnemyManager::C_TUTLE, { data.positionX,data.positionY });
			else if (data.name == "F_Flower1")
				EnemyManager::Get()->CreateEnemy(EnemyManager::F_TUTLE, { data.positionX,data.positionY });
			else if (data.name == "F_FlyTutle1")
				EnemyManager::Get()->CreateEnemy(EnemyManager::F_FLYTUTLE, { data.positionX,data.positionY });
		}
	}
}
void MarioDataManager::LoadEditerStage(string stageName)
{
	LoadMapData(stageName);
	LoadCharacterData(stageName);
	LoadItemData(stageName);

	for(TileData tileData : loadTileData)
		TileMapManager::Get()->LoadTileData(tileData);
	for (CharacterData characterData : loadCharacterData)
		TileMapManager::Get()->LoadCharacterData(characterData);
}
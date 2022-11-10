#pragma once


class TileTextureData : public Singleton<TileTextureData>
{
public:
	enum TAG
	{
		NONE, BACKGROUND, BLOCK, INDESTRUCTIBLE_BLOCK, 
		ITEMBLOCK, EVENT, CHARACTER, ITEM
	};
	struct TileData
	{
		TAG tag;
		string tileName;
	};

public:
	TileTextureData();
	~TileTextureData();
	void CreateTexture();
	void SetTexture(wstring file, string key, TAG tag);
	void SetTexture(wstring file, string key, TAG tag, int sizeX, int sizeY, int frameX, int frameY);

	Texture* GetTextureData(string key)
	{
		return textures[key];
	}
	TileData GetTileInfo(int key) { return tileInfo[key]; }
	unordered_map<int, TileData> GetTileInfo() { return tileInfo; }

	int GetTileCount() { return tileCount; }

private:
	Texture* texture;
	unordered_map<string, Texture*> textures;
	unordered_map<int, TileData> tileInfo;
	int tileCount = 0;
	//vector<string> keys;
};
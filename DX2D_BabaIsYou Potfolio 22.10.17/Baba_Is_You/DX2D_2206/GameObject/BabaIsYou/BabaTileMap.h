#pragma once

class BabaTileMap : public Transform
{
private:
	const Vector2 TILE_SIZE = { 48,48 };

	struct Data
	{
		string key;
		Vector2 pos;
	};

public:
	BabaTileMap(UINT width, UINT height);
	~BabaTileMap();

	void Update();
	void Render();
	void OneMoreRender(string key);

	void SetBufferSize(string key, int count);

	void ClickTile(Object* selectSample);
	void DeleteObjTile();

	void SetColliderOff();

	vector<Object*> GetTiles() { return tiles; }
	vector<Object*> GetBGTiles() { return bgTiles; }

	map<string, InstanceQuad*> GetInstanceQuads() { return instanceQuads; }

	void Save(string file);
	void Load(string file); 
private:
	void CreateTile();

	void ClearBGTile();
	void ClearOBJTile();

	void SetMapPosition();

private:
	UINT width = 0, height = 0;

	map<string, InstanceQuad*> instanceQuads;
	vector<Object*> tiles;
	vector<Object*> bgTiles;

	Vector2 tileSize;
	Vector2 position;
};
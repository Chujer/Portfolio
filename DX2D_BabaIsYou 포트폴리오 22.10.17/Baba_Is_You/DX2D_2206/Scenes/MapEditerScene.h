#pragma once

class MapEditerScene : public Scene
{
private:
	enum Mode
	{

	};
public:
	MapEditerScene();
	~MapEditerScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	//void ClickSampleBtn(void* sampleBtn);

private:
	void CreateSample();

	//void Save();
	//void Load();

private:
	Vector2 sampleTileSize = { 48, 48 };
	map<string, InstanceQuad*> instanceQuads;

	Object* selectTile;
	map<string, vector<Object*>> sampleTile;
	vector<Object*> tileMap;
	map<string, bool> checkTiles;
	bool tempNameBool = false;

	Tile::Type selectType = Tile::BG;


};
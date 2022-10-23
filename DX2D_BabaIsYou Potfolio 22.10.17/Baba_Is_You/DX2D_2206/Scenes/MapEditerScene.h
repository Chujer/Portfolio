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

private:
	void CreateSample();
	void SortSample();
	void ClickSampleBtn();

	void Save();
	void Load();

private:
	Vector2 sampleTileSize = { 48, 48 };
	map<string, InstanceQuad*> instanceQuads;

	Object* selectTile = nullptr;
	map<string, vector<Object*>> sampleTile;

	BabaTileMap* tileMap = nullptr;

	map<string, bool> checkTiles;

	Quad* backGround;

	int size[2] = {0};

	string projectPath;

};
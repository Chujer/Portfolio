#pragma once

class MapEditerUIManager : public Singleton<MapEditerUIManager>
{
public:
	MapEditerUIManager();
	~MapEditerUIManager();

	void Update();
	void Render(HDC hdc);

	ImageRect* GetPanel() { return panel; }
	vector<Tile*> GetTile() { return tiles; }

private:
	void MovePanel();
	void CreatePanel();
	void CreateUITile();
	void MoveUITile();

private:
	ImageRect* panel;
	Vector2 firstPanelPos;
	Rect* tempPanelInfo;
	bool isOpen = false;

	vector<Tile*> tiles;
	Vector2 offset = {15,10};
	Vector2 panelLT;
	Vector2 panelMovePoint;
};
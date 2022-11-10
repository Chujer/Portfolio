class Tile : public ImageRect
{
public:
	Tile();
	~Tile();

	TileData& TileInfo() { return tileInfo; }
	bool& select() { return selectTile; }

	virtual void SetType(int type) {};
	virtual void CreateAnimation() {};
	virtual void SetItem(string name) {};
	void Update();
	void Render(HDC hdc);
	void NomalRender(HDC hdc);

	void SetPos(Vector2 pos)
	{
		this->pos = pos;
	}
	TileData GetTileInfo() { return tileInfo; }

	void TileMove();
	void CreateTile(Vector2 pos, int textureNum);
	void CreateTile(Vector2 pos, string name, TAG tag,string itemName = "");

	void SetTexture(string key)
	{
		tileInfo.tileName = key;
		ImageRect::SetTexture(TileTextureData::Get()->GetTextureData(key));
		size = { WIN_WIDTH / 16,WIN_HEIGHT / 14 };
		camRect->Size() = size;
	}


	void SetTexture(Texture* texture)
	{
		ImageRect::SetTexture(texture);
	}

	void Break();
	virtual void SetEvent(string name) {}
	void StartEvent() { Event(); }
protected:
	TileData tileInfo;
	function<void()> Event;
	bool selectTile = false;
	HPEN selectPen;
	HPEN oldPen;
};
#pragma once

class Item;

class ItemBlockTile : public Tile
{
private:
	enum State
	{
		USE, USED
	};

public:
	ItemBlockTile();
	~ItemBlockTile();

	void Update();
	void Render(HDC hdc);

	void CreateBlock(Vector2 pos);
	virtual void SetItem(string name) override;


	void CreateAnimation();

	void MakeItem();
	Item* GetItem()
	{
		return item;
	}

private:
	void SetAction(State type);

private:
	State state = USE;
	map<State, Animation*> animations;
	Item* item;
};
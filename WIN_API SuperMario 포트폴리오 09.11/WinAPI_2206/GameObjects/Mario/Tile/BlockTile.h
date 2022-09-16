#pragma once

class BlockTile : public Tile
{
public:
	BlockTile();
	~BlockTile();

	void Render(HDC hdc);
	/*void SetPos(Vector2 pos)
	{
		this->pos = pos;
	}*/
	void Break();

private:
};
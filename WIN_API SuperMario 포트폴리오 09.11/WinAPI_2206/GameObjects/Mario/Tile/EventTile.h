#pragma once

class EventTile : public Tile
{
public:
	EventTile();
	~EventTile();

	virtual void SetEvent(string name) override;
};
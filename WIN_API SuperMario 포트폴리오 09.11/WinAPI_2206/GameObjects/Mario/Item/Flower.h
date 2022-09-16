#pragma once

class Flower : public Item
{
public:
	Flower();
	~Flower();

	virtual void Move() override;
	virtual void SetItemTexture();
	virtual void IsOnTheGround(Vector2 Ground);
	virtual void StartSound() override;
private:

};
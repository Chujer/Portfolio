#pragma once

class Mushroom : public Item
{
private:
	const float GRAVITY = 980.0f;

public:
	Mushroom();
	~Mushroom();
	
	virtual void Move() override;
	virtual void SetItemTexture();
	virtual void IsOnTheGround(Vector2 Ground);
	virtual void StartSound() override;

private:
};
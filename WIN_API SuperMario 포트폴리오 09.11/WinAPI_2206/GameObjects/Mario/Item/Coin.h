#pragma once

class Coin : public Item
{
public:
	Coin();
	~Coin();

	virtual void Move() override;
	virtual void SetItemTexture();
	virtual void Render(HDC hdc) override;
	virtual void IsOnTheGround(Vector2 Ground) override;
	void NomalRender(HDC hdc) { ImageRect::Render(hdc,ani->GetFrame()); }
	virtual void StartSound() override;

	void AniUpdate();

private:
	Animation* ani;
	bool startAni = false;
};
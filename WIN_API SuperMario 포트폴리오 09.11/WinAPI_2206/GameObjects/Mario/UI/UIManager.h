#pragma once

class UIManger : public Singleton<UIManger>
{
private:

public:
	UIManger();
	~UIManger();

	void Update();
	void InGameRender(HDC hdc);
	void UIRender(HDC hdc);

private:
	HFONT hfont;
	Coin* coin;
};
#include "Framework.h"
#include "UIManager.h"

UIManger::UIManger()
{
	hfont = CreateFont(30, 20, 0, 0, 1, false, false, false, HANGUL_CHARSET,
		100, 0, 0, 0, L"배달의민족 도현");
	coin = new Coin;
	coin->Pos() = { WIN_WIDTH * 0.32f,63 };
	coin->SetItemTexture();
	coin->Size() *= 0.7f;

	
}

UIManger::~UIManger()
{
}

void UIManger::InGameRender(HDC hdc)
{
	coin->AniUpdate();
	SelectObject(hdc, hfont);
	SetTextColor(hdc, RGB(255, 255, 255));
	string str;
	string nextstr;
	str = "MARIO";
	nextstr = to_string(MarioGameManager::Get()->Score());
	TextOutA(hdc, WIN_WIDTH*0.1f, 20, str.c_str(), str.length());
	TextOutA(hdc, WIN_WIDTH*0.1f, 50, nextstr.c_str(), nextstr.length());
	coin->NomalRender(hdc);
	str = " X " + to_string(MarioGameManager::Get()->Coin());
	TextOutA(hdc, WIN_WIDTH * 0.335f, 50, str.c_str(), str.length());
	str = "WORLD 1 - " + to_string(MarioGameManager::Get()->StageNum());
	TextOutA(hdc, WIN_WIDTH * 0.5f, 20, str.c_str(), str.length());
	str = "TIME ";
	nextstr = to_string(MarioGameManager::Get()->GameTime());
	TextOutA(hdc, WIN_WIDTH * 0.8f, 20, str.c_str(), str.length());
	TextOutA(hdc, WIN_WIDTH * 0.81f, 50, nextstr.c_str(), nextstr.length());
}

void UIManger::UIRender(HDC hdc)
{
}


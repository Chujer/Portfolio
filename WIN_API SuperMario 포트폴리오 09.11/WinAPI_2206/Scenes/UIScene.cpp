#include "Framework.h"
#include "UIScene.h"

UIScene::UIScene()
{
	hbrush = CreateSolidBrush(BLACK);
	mario = new ImageRect(TEXTURE->Add(L"Textures/Mario/0.bmp",18,18));
	mario->Size() *= 3.0f;
	mario->Pos() = { WIN_WIDTH * 0.42f, WIN_HEIGHT * 0.5f };
	Audio::Get()->Add("Ending", "Sounds/GameOver.wav", true, true);
}

UIScene::~UIScene()
{
	delete mario;
}

void UIScene::Update()
{
	time += DELTA;
	if (MarioGameManager::Get()->StageNum() < 3)
	{
		if (time > WAIT_TIME)
		{
			time = 0;
			MarioGameManager::Get()->ChangeScene("PlayScene");
			MarioGameManager::Get()->SetStage();
		}
	}
	else if(MarioGameManager::Get()->StageNum() == 3)
	{
		Audio::Get()->Stop("stage2BGM");
		Audio::Get()->Play("Ending", 0.5f);
		MarioGameManager::Get()->StageNum()++;
	}
	else
	{

	}
		
}

void UIScene::Render(HDC hdc)
{
	if (MarioGameManager::Get()->StageNum() < 3)
	{
		SelectObject(hdc, hbrush);
		Rectangle(hdc, -1, -1, WIN_WIDTH + 1, WIN_HEIGHT + 1);

		//TextOutA(hdc, WIN_WIDTH * 0.5f, 20, str.c_str(), str.length());
		UIManger::Get()->InGameRender(hdc);

		wstring	textLife = L"WORLD 1 - " + to_wstring(MarioGameManager::Get()->StageNum());
		wstring Score = to_wstring(MarioGameManager::Get()->PlayerLife());
		TextOut(hdc, WIN_WIDTH * 0.37f, WIN_HEIGHT * 0.34f, textLife.c_str(), textLife.length());

		mario->Render(hdc);
		textLife = L" X ";
		TextOut(hdc, WIN_WIDTH * 0.47f, WIN_HEIGHT * 0.49f, textLife.c_str(), textLife.length());
		TextOut(hdc, WIN_WIDTH * 0.55f, WIN_HEIGHT * 0.49f, Score.c_str(), Score.length());
	}
	else
	{
		SelectObject(hdc, hbrush);
		Rectangle(hdc, -1, -1, WIN_WIDTH + 1, WIN_HEIGHT + 1);

		wstring ending = L"THANK YOU FOR PLAYING";
		TextOut(hdc, WIN_WIDTH * 0.26f, WIN_HEIGHT * 0.34f, ending.c_str(), ending.length());
	}
}

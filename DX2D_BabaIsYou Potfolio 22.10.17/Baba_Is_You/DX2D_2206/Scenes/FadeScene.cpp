#include "Framework.h"
#include "FadeScene.h"

FadeScene::FadeScene()
{
	for (int i = 0; i < 4; i++)
	{
		quads[i] = new Quad(L"Textures/Fade.png");
	}

	quads[0]->Position() = { -CENTER_X,CENTER_Y };
	quads[1]->Position() = { WIN_WIDTH+CENTER_X,CENTER_Y };
	quads[2]->Position() = { CENTER_X,-CENTER_Y };
	quads[3]->Position() = { CENTER_X,WIN_HEIGHT+CENTER_Y };

	firstPosition[0] = { -CENTER_X,CENTER_Y };
	firstPosition[1] = { WIN_WIDTH+CENTER_X,CENTER_Y };
	firstPosition[2] = { CENTER_X,-CENTER_Y };
	firstPosition[3] = { CENTER_X,WIN_HEIGHT+CENTER_Y };


	for (int i = 0; i < 4; i++)
	quads[i]->UpdateWorld();
}

FadeScene::~FadeScene()
{
}

void FadeScene::FadeIn()
{
	for (int i = 0; i < 4; i++)
	{
		quads[i]->Position() = LERP(quads[i]->Position(), Vector2(CENTER_X, CENTER_Y), DELTA);
	}
	if (quads[0]->Position().x > 100.0f)
		mode = FADE_OUT;
}

void FadeScene::FadeOut()
{
	for (int i = 0; i < 4; i++)
	{
		quads[i]->Position() = LERP(quads[i]->Position(), firstPosition[i], DELTA*10.0f);
	}
	if (quads[0]->Position() == firstPosition[0])
		mode = NONE;
}

void FadeScene::Stop()
{
}

void FadeScene::Update()
{
	if (BabaGameManager::Get()->CallLoad())
	{
		mode = FADE_IN;
		BabaGameManager::Get()->CallLoad() = false;
	}
	switch (mode)
	{
	case FadeScene::FADE_IN:
		FadeIn();
		break;
	case FadeScene::FADE_OUT:
		FadeOut();
		break;
	case FadeScene::NONE:
		break;
	default:
		break;
	}
	for (int i = 0; i < 4; i++)
	{
		quads[i]->UpdateWorld();
	}
}

void FadeScene::Render()
{
	for (int i = 0; i < 4; i++)
	{
		quads[i]->Render();
	}
}

void FadeScene::PostRender()
{
}

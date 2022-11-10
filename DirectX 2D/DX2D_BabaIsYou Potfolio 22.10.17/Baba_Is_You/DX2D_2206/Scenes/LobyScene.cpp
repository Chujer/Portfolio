#include "Framework.h"
#include "LobyScene.h"

LobyScene::LobyScene()
{
	quad = new Quad(L"Textures/Lobby.png");
	pressQuad = new Quad(L"Textures/PressTest.png");
	pressQuad->Position() = { CENTER_X,CENTER_Y };
	quad->Position() = { CENTER_X,CENTER_Y };
	StartPos = quad->Position();
	SetEndPos();

	endColor = { 1,1,1,1.0f };


	quad->UpdateWorld();
	pressQuad->UpdateWorld();
}

LobyScene::~LobyScene()
{
	delete quad;
}

void LobyScene::Update()
{
	if (!quad->Active()) return;

	if (!BabaGameManager::Get()->IsLobby())
		quad->SetActive(false);

	quad->UpdateWorld();

	if (Keyboard::Get()->IsAnyKey())
	{
		BabaGameManager::Get()->CallLoad() = true;
	}
	if(BabaGameManager::Get()->FadeEnd() == true)
		BabaGameManager::Get()->IsLobby() = false;

	endColor.w -= DELTA * blinkSpeed;
	if (endColor.w < 0 || endColor.w > 1.0f)
	{
		blinkSpeed *= -1;
	}
	pressQuad->GetColorBuffer()->Set(endColor.x, endColor.y, endColor.z, endColor.w);

	//quad->Position() += direction * 5.0f * DELTA;
	//if ((quad->Position() - endPos).Length() < 20.0f)
	//	SetEndPos();


}

void LobyScene::Render()
{
	if (!quad->Active()) return;


	pressQuad->GetVertexShader()->Set();
	pressQuad->GetPixelShader()->Set();

	quad->Render();
	pressQuad->Render();
}

void LobyScene::PostRender()
{
}

void LobyScene::SetEndPos()
{
	endPos.x = Random(-20.0f, 20.0f);
	endPos.y = Random(-20.0f, 20.0f);
	endPos = StartPos + endPos;
	direction = endPos - quad->Position();
}

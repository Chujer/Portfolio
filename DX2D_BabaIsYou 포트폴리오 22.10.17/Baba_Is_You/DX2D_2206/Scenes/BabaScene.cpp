#include "Framework.h"
#include "BabaScene.h"

BabaScene::BabaScene()
{
	temp = new Object();
	temp->Position() = { CENTER_X,CENTER_Y };
	temp->Scale() *= 2;
	temp->UpdateWorld();
}

BabaScene::~BabaScene()
{
	delete temp;
}

void BabaScene::Update()
{
	temp->Update();
	temp->UpdateWorld();
}

void BabaScene::Render()
{
	temp->Render();
}

void BabaScene::PostRender()
{
}

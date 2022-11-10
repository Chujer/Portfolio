#include "Framework.h"
#include "MapEditerScene.h"

MapEditerScene::MapEditerScene()
{
	TileMapManager::Get();
	texture = new ImageRect(TEXTURE->Add(L"Textures/BigMap.bmp", 8000, 768));
	texture->Pos() += texture->Half();
	MapEditerUIManager::Get();
	Camera::Get()->SetMapRect(texture);
	Camera::Get()->SetTarget(nullptr);
}

MapEditerScene::~MapEditerScene()
{
	delete texture;
	TileMapManager::Delete();
	
}

void MapEditerScene::Update()
{
	TileMapManager::Get()->Update();
	MapEditerUIManager::Get()->Update();
}

void MapEditerScene::Render(HDC hdc)
{
	TileMapManager::Get()->Render(hdc);
	MapEditerUIManager::Get()->Render(hdc);

}
